#include <stdlib.h>
#include <iomanip>
#include <string>
#include <ctime>

#include "../../libs/Auction.h"
#include "../../libs/Dashboard.h"
#include "../../libs/Database.h"
#include "../../libs/Item.h"
#include "../../libs/Member.h"
#include "../../libs/Transaction.h"
#include "../..//libs/waiting.h"
#include "../../libs/clearing.h"

void Dashboard::displayTransactionDetailedMenu(Transaction *transaction)
{
  clearing();
  std::cout << "====================================" << std::endl;
  std::cout << "        Transaction Detailed        " << std::endl;
  std::cout << "====================================" << std::endl;
  std::cout << std::endl;

  Database database;

  std::cout << "Transaction ID: " << transaction->getTransactionID()
            << std::endl;
  time_t transactionTime = transaction->getTransactionTime();
  std::cout << "Transaction Date: " << std::string(ctime(&transactionTime))
            << std::endl;
  std::string sellerName =
      database.getMemberByID(transaction->getSellerID())->getFullname();
  std::cout << "Seller name: " << sellerName << std::endl;
  std::string buyerName =
      database.getMemberByID(transaction->getBuyerID())->getFullname();
  std::cout << "Buyer name: " << buyerName << std::endl;
  Item item = *database.getItemByID(transaction->getItemID());
  std::string itemName = item.getItemName();
  std::cout << "Item name: " << itemName << std::endl;
  std::cout << "Price: " << item.getCurrentBidAmount() << " CP" << std::endl;

  std::cout << std::endl;
  std::cout << "====================================" << std::endl;
  std::cout << "         Transaction reviews        " << std::endl;
  std::cout << "====================================" << std::endl;
  std::cout << std::endl;

  std::vector<Review> filteredReviews;
  for (Review &review : database.getAllReviews())
  {
    if ((review.getReviewerID() == transaction->getBuyerID() &&
         review.getMemberID() == transaction->getSellerID()) ||
        (review.getReviewerID() == transaction->getSellerID() &&
         review.getMemberID() == transaction->getBuyerID()))
    {
      std::cout << "Reviewer: "
                << database.getMemberByID(review.getReviewerID())->getFullname()
                << std::endl;
      std::cout << "Rating: " << review.getRating() << std::endl;
      std::cout << "Content: " << review.getContent() << std::endl;
      filteredReviews.push_back(review);
    }
  }
  if (filteredReviews.size() == 0)
  {
    std::cout << "No reviews available." << std::endl;
  }

  std::cout << std::endl
            << "0. Back to member menu." << std::endl;
  std::cout << "1. Write review." << std::endl;

  return handleTransactionDetailedMenu(transaction, false);
}

void Dashboard::handleTransactionDetailedMenu(Transaction *transaction,
                                              bool clear)
{
  if (clear)
  {
    clearing();
  }

  std::cout << "Enter your choice: ";
  int choice;
  std::cin >> choice;

  // Check if the input is valid
  if (std::cin.fail())
  {
    std::cin.clear();
    std::cin.ignore(1000, '\n');
    std::cout << "Invalid choice. Please try again." << std::endl;
    return Dashboard::displayTransactionDetailedMenu(transaction);
  }

  switch (choice)
  {
  case 0:
  {
    return Dashboard::displayMemberMenu();
  }
  case 1:
  {
    clearing();
    Database database;
    Member buyer = *database.getMemberByID(transaction->getBuyerID());
    Member seller = *database.getMemberByID(transaction->getSellerID());

    // In case of the buyer is the current user
    if (buyer.getMemberID() == transaction->getBuyerID())
    {
      // Check if the buyer has already reviewed the seller
      for (Review &review : database.getAllReviews())
      {
        if (review.getReviewerID() == buyer.getMemberID() &&
            review.getMemberID() == seller.getMemberID())
        {
          std::cout << "You have already reviewed the seller." << std::endl;
          waiting(3);
          return displayTransactionDetailedMenu(transaction);
        }
      }

      std::cout << "Enter your rating (1-5): ";
      int rating;
      std::cin >> rating;

      // check if the input is valid
      if (std::cin.fail() || rating < 1 || rating > 5)
      {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Invalid rating. Please try again." << std::endl;
        return handleTransactionDetailedMenu(transaction, false);
      }

      std::string content;
      std::cout << "Enter your review (no comma): ";
      getline(std::cin >> std::ws, content);

      Review review(seller, buyer, content, rating);
      review.save();

      // Calculate the average rating of the seller
      // Get all review of the seller
      std::vector<Review> sellerReviews;
      int total = 3 + rating; // Default rating
      for (Review &review : database.getAllReviews())
      {
        std::cout << review.getMemberID() << " " << seller.getMemberID()
                  << std::endl;
        if (review.getMemberID() == seller.getMemberID())
        {
          sellerReviews.push_back(review);
          total += review.getRating();
        }
      }
      seller.setRating((total) / (sellerReviews.size() + 2));
      seller.save();
    }
    else
    {
      // Check if the seller has already reviewed the buyer
      for (Review &review : database.getAllReviews())
      {
        if (review.getReviewerID() == seller.getMemberID() &&
            review.getMemberID() == buyer.getMemberID())
        {
          std::cout << "You have already reviewed the buyer." << std::endl;
          waiting(3);
          return displayTransactionDetailedMenu(transaction);
        }
      }

      std::cout << "Enter your rating (1-5): ";
      int rating;
      std::cin >> rating;

      // check if the input is valid
      if (std::cin.fail() || rating < 1 || rating > 5)
      {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Invalid rating. Please try again." << std::endl;
        return handleTransactionDetailedMenu(transaction, false);
      }

      std::string content;
      std::cout << "Enter your review (no comma): ";
      getline(std::cin >> std::ws, content);

      Review review(buyer, seller, content, rating);
      review.save();

      // Calculate the average rating of the buyer
      // Get all review of the buyer
      std::vector<Review> buyerReviews;
      int total = 3; // Default rating
      for (Review &review : database.getAllReviews())
      {
        if (review.getMemberID() == buyer.getMemberID())
        {
          buyerReviews.push_back(review);
          total += review.getRating();
        }
      }
      buyer.setRating(total / (buyerReviews.size() + 1));
      buyer.save();
    }
    return Dashboard::displayTransactionDetailedMenu(transaction);
  }
  default:
    std::cout << "Invalid choice. Please try again." << std::endl;
    return handleTransactionDetailedMenu(transaction, false);
  }
}
