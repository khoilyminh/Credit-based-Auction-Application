#ifndef DATABASE_H
#define DATABASE_H

#include <vector>

#include "./Admin.h"
#include "./Auction.h"
#include "./Bid.h"
#include "./Item.h"
#include "./Member.h"
#include "./Review.h"
#include "./Transaction.h"
#include "./User.h"

class Database {
 private:
  std::vector<User> users;
  /** This function is used to save the whole user list to file. */
  void saveUsersToFile();

  std::vector<Member> members;
  /** This function is used to save the whole member list to file. */
  void saveMembersToFile();

  std::vector<Admin> admins;
  /** This function is used to save the whole admin list to file. */
  void saveAdminsToFile();

  std::vector<Auction> auctions;
  /** This function is used to save the whole auction list to file. */
  void saveAuctionsToFile();

  std::vector<Item> items;
  /** This function is used to save the whole member list to file. */
  void saveItemsToFile();

  std::vector<Bid> bids;
  /** This function is used to save the whole bid list to file. */
  void saveBidsToFile();

  std::vector<Transaction> transactions;
  /** This function is used to save the whole transaction list to file. */
  void saveTransactionsToFile();

  std::vector<Review> reviews;
  /** This function is used to save the whole review list to file. */
  void saveReviewsToFile();

 public:
  Database();

  // ------- User methods -------

  /** This function get all user in the database. */
  std::vector<User> getAllUsers();
  /** This function is used to get user by userID. */
  User *getUserByID(std::string userID);
  /** This function is used to add or update user in the database. */
  void saveUser(User *user);
  /** This function is used to remove a user from the database. */
  void removeUser(User user);

  // ------- Member methods -------

  /** This function get all member in the database. */
  std::vector<Member> getAllMembers();
  /** This function is used to get member by memberID. */
  Member *getMemberByID(std::string memberID);
  /** This function is used to add or update member in the database. */
  void saveMember(Member *member);
  /** This function is used to remove a member from the database. */
  void removeMember(Member member);

  // ------- Admin methods -------

  /** This function get all admin in the database. */
  std::vector<Admin> getAllAdmins();
  /** This function is used to get admin by adminID. */
  Admin *getAdminByID(std::string adminID);
  /** This function is used to add or update admin in the database. */
  void saveAdmin(Admin *admin);
  /** This function is used to remove a admin from the database. */
  void removeAdmin(Admin admin);

  // ------- Item Methods -------

  /** This function get all member in the database. */
  std::vector<Item> getAllItems();
  /** This function is used to get member by itemID. */
  Item *getItemByID(std::string itemID);
  /** This function is used to add or update an Item in the database. */
  void saveItem(Item *item);
  /** This function is used to remove an Item from the database. */
  void removeItem(Item item);

  // ------- Auction Methods -------
  /** This function get all auction in the database. */
  std::vector<Auction> getAllAuctions();
  /** This function is used to get auction by auctionID. */
  Auction *getAuctionByID(std::string auctionID);
  /** This function is used to add or update an Auction in the database. */
  void saveAuction(Auction *auction);
  /** This function is used to remove an Auction from the database. */
  void removeAuction(Auction auction);

  // ------- Bid Methods -------

  /** This function is used to get all bids of an auction. */
  std::vector<Bid> getAllBids();
  /** This function is used to get all bids of an auction. */
  std::vector<Bid> getBidsByItemID(std::string auctionID);
  /** This function is used to get all bids of an auction. */
  std::vector<Bid> getBidsByMemberID(std::string memberID);
  /** This function is used to add or update a Bid in the database. */
  void saveBid(Bid *bid);
  /** This function is used to remove a Bid from the database. */
  void removeBid(Bid bid);

  // ------- Transaction Methods -------

  /** This function is used to get all transactions */
  std::vector<Transaction> getAllTransactions();
  /** This function is used to get all transactions of a member */
  std::vector<Transaction> getTransactionsByMemberID(std::string memberID);
  /** This function is used to get all transactions of an item */
  std::vector<Transaction> getTransactionsByItemID(std::string itemID);
  /** This function is used to add or update a Transaction in the database. */
  void saveTransaction(Transaction *transaction);
  /** This function is used to remove a Transaction from the database. */
  void removeTransaction(Transaction transaction);

  // ------- Review Methods -------

  /** This function is used to get all reviews */
  std::vector<Review> getAllReviews();
  /** This function is used to get all reviews of a member */
  std::vector<Review> getReviewsByMemberID(std::string memberID);
  /** This function is used to add or update a Review in the database. */
  void saveReview(Review *review);
  /** This function is used to remove a Review from the database. */
  void removeReview(Review review);
};

#endif