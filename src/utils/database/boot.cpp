#include <unistd.h>
#include <fstream>
#include <iostream>
#include <vector>

#include "../../libs/Database.h"
#include "../../libs/Item.h"
#include "../../libs/Member.h"
#include "../../libs/Review.h"
#include "../../libs/Transaction.h"
#include "../../libs/User.h"

std::vector<User> getAllUsersFromDatabase()
{
  std::vector<User> users;
  std::ifstream file("./data/users.txt", std::ios::in);
  std::string line;
  while (std::getline(file, line))
  {
    // The first value is the userID, the second value is the username, and the
    // third value is the password, the forth value will be status.
    std::string userID = line.substr(0, line.find(", "));
    line = line.substr(line.find(", ") + 1);
    std::string username = line.substr(1, line.find(", ") - 1);
    line = line.substr(line.find(", ") + 1);
    std::string password = line.substr(1, line.find(", ") - 1);
    line = line.substr(line.find(", ") + 2);
    bool status = line.substr(line.find(", ") + 1) == "1";
    // Create a new user object and add it to the users vector.
    User user(userID, username, password, status);
    users.push_back(user);
  }
  file.close();
  return users;
}

std::vector<Member> getAllMembersFromDatabase()
{
  std::vector<Member> members;
  std::ifstream file("./data/members.txt", std::ios::in);
  std::string line;
  while (std::getline(file, line))
  {
    // The first value is the memberID, the second value is the fullname, the
    // third value is the phoneNumber, the fourth value is the email, the fifth
    // value is the creditPoint, the sixth value is the rating, the seventh
    // value is the credit, and the eighth value is the userID.
    std::string memberID = line.substr(0, line.find(", "));
    line = line.substr(line.find(" ") + 1);
    std::string fullname = line.substr(0, line.find(", "));
    line = line.substr(line.find(", ") + 1);
    std::string phoneNumber = line.substr(1, line.find(", ") - 1);
    line = line.substr(line.find(", ") + 1);
    std::string email = line.substr(1, line.find(", ") - 1);
    line = line.substr(line.find(", ") + 1);
    float rating = std::stof(line.substr(1, line.find(", ") - 1));
    line = line.substr(line.find(", ") + 1);
    int credit = std::stoi(line.substr(1, line.find(", ") - 1));
    line = line.substr(line.find(", ") + 1);
    std::string userID = line.substr(1, line.find(", ") - 1);
    line = line.substr(line.find(", ") + 1);
    std::string IDNumber = line.substr(1, line.find(", ") - 1);
    // Create a new member object and add it to the members vector.
    Member member(memberID, fullname, phoneNumber, email, rating, credit,
                  userID, IDNumber);
    members.push_back(member);
  }
  file.close();
  return members;
}

std::vector<Admin> getAllAdminsFromDatabase()
{
  std::vector<Admin> admins;
  std::ifstream file("./data/admins.txt", std::ios::in);
  std::string line;
  while (std::getline(file, line))
  {
    // The first value is the adminID, the second value is the adminID, and the
    // third value is the userID.
    std::string adminID = line.substr(0, line.find(", "));
    line = line.substr(line.find(", ") + 1);
    std::string userID = line.substr(1, line.find(", "));
    // Create a new admin object and add it to the admins vector.
    Admin admin(adminID, userID);
    admins.push_back(admin);
  }
  file.close();
  return admins;
}

std::vector<Auction> getAllAuctionsFromDatabase()
{
  std::vector<Auction> auctions;
  std::ifstream file("./data/auctions.txt", std::ios::in);
  std::string line;
  while (std::getline(file, line))
  {
    // The first value is the auctionID, the second value is the itemID, the
    // third value is the sellerID, the fourth value is the startingPrice, the
    // fifth value is the currentPrice, the sixth value is the highestBidderID,
    // and the seventh value is the status.
    std::string auctionID = line.substr(0, line.find(", "));
    line = line.substr(line.find(", ") + 1);
    std::string auctionName = line.substr(1, line.find(", ") - 1);
    line = line.substr(line.find(", ") + 1);
    std::string startTimeStr = line.substr(1, line.find(", ") - 1);
    long startTimeAuction = std::stol(startTimeStr);
    line = line.substr(line.find(", ") + 1);
    std::string endTimeStr = line.substr(1, line.find(", ") - 1);
    long endTimeAuction = std::stol(endTimeStr);
    line = line.substr(line.find(", ") + 1);
    // Create a new auction object and add it to the auctions vector.
    Auction auction(auctionID, auctionName, startTimeAuction, endTimeAuction);
    auctions.push_back(auction);
  }
  file.close();
  return auctions;
}

std::vector<Item> getAllItemsFromDatabase()
{
  std::vector<Item> items;
  std::ifstream file("./data/items.txt", std::ios::in);
  std::string line;
  while (std::getline(file, line))
  {
    std::string itemID = line.substr(0, line.find(", "));
    line = line.substr(line.find(", ") + 1);
    std::string itemName = line.substr(1, line.find(", ") - 1);
    line = line.substr(line.find(", ") + 1);
    std::string category = line.substr(1, line.find(", ") - 1);
    line = line.substr(line.find(", ") + 1);
    std::string description = line.substr(1, line.find(", ") - 1);
    line = line.substr(line.find(", ") + 1);
    std::string sellerID = line.substr(1, line.find(", ") - 1);
    line = line.substr(line.find(", ") + 1);
    float startingBidAmount = std::stof(line.substr(1, line.find(", ") - 1));
    line = line.substr(line.find(", ") + 1);
    float currentBidAmount = std::stof(line.substr(1, line.find(", ") - 1));
    line = line.substr(line.find(", ") + 1);
    float bidIncrement = std::stof(line.substr(1, line.find(", ") - 1));
    line = line.substr(line.find(", ") + 1);
    float minBuyerRating = std::stof(line.substr(1, line.find(", ") - 1));
    line = line.substr(line.find(", ") + 1);
    std::string auctionID = line.substr(1, line.find(", "));

    Item item(itemID, itemName, category, sellerID, description,
              startingBidAmount, currentBidAmount, bidIncrement, minBuyerRating,
              auctionID);
    items.push_back(item);
  }
  file.close();
  return items;
}

std::vector<Bid> getAllBidsFromDatabase()
{
  std::vector<Bid> bids;
  std::ifstream file("./data/bids.txt", std::ios::in);
  std::string line;
  while (std::getline(file, line))
  {
    std::string bidID = line.substr(0, line.find(", "));
    line = line.substr(line.find(", ") + 1);
    std::string memberID = line.substr(1, line.find(", ") - 1);
    line = line.substr(line.find(", ") + 1);
    std::string itemID = line.substr(1, line.find(", ") - 1);
    line = line.substr(line.find(", ") + 1);
    float bidAmount = std::stof(line.substr(1, line.find(", ") - 1));
    line = line.substr(line.find(", ") + 1);
    bool automaticBid = std::stoi(line.substr(1, line.find(", ") - 1));
    line = line.substr(line.find(", ") + 1);
    float limitPrice = std::stof(line.substr(1, line.find(", ") - 1));

    Bid bid(bidID, memberID, itemID, bidAmount, automaticBid, limitPrice);
    bids.push_back(bid);
  }
  file.close();
  return bids;
}

std::vector<Transaction> getAllTransactionsFromDatabase()
{
  std::vector<Transaction> transactions;
  std::ifstream file("./data/transactions.txt", std::ios::in);
  std::string line;
  while (std::getline(file, line))
  {
    std::string transactionID = line.substr(0, line.find(", "));
    line = line.substr(line.find(", ") + 1);
    std::string buyerID = line.substr(1, line.find(", ") - 1);
    line = line.substr(line.find(", ") + 1);
    std::string sellerID = line.substr(1, line.find(", ") - 1);
    line = line.substr(line.find(", ") + 1);
    std::string bidID = line.substr(1, line.find(", ") - 1);
    line = line.substr(line.find(", ") + 1);
    std::string itemID = line.substr(1, line.find(", ") - 1);
    line = line.substr(line.find(", ") + 1);
    long time = std::stol(line.substr(1, line.find(", ") - 1));

    Transaction transaction(transactionID, buyerID, sellerID, bidID, itemID,
                            time);
    transactions.push_back(transaction);
  }
  file.close();
  return transactions;
}

std::vector<Review> getAllReviewsFromDatabase()
{
  std::vector<Review> reviews;
  std::ifstream file("./data/reviews.txt", std::ios::in);
  std::string line;
  while (std::getline(file, line))
  {
    std::string reviewID = line.substr(0, line.find(", "));
    line = line.substr(line.find(", ") + 1);
    std::string memberID = line.substr(1, line.find(", ") - 1);
    line = line.substr(line.find(", ") + 1);
    std::string reviewerID = line.substr(1, line.find(", ") - 1);
    line = line.substr(line.find(", ") + 1);
    std::string content = line.substr(1, line.find(", ") - 1);
    line = line.substr(line.find(", ") + 1);
    float rating = std::stof(line.substr(1, line.find(", ") - 1));

    Review review(reviewID, memberID, reviewerID, content, rating);
    reviews.push_back(review);
  }
  file.close();
  return reviews;
}

Database::Database()
{
  this->users = getAllUsersFromDatabase();
  this->members = getAllMembersFromDatabase();
  this->admins = getAllAdminsFromDatabase();
  this->auctions = getAllAuctionsFromDatabase();
  this->items = getAllItemsFromDatabase();
  this->bids = getAllBidsFromDatabase();
  this->transactions = getAllTransactionsFromDatabase();
  this->reviews = getAllReviewsFromDatabase();
}