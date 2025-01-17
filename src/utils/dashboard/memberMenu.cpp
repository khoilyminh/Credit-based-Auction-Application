#include <stdlib.h>
#include <string>
#include <ctime>

#include "../../libs/Auction.h"
#include "../../libs/Bid.h"
#include "../../libs/Dashboard.h"
#include "../../libs/Database.h"
#include "../../libs/Item.h"
#include "../../libs/Member.h"
#include "../../libs/Transaction.h"
#include "../..//libs/waiting.h"
#include "../../libs/clearing.h"

void Dashboard::displayMemberMenu()
{
  clearing();
  std::cout << "====================================" << std::endl;
  std::cout << "            Member Menu             " << std::endl;
  std::cout << "====================================" << std::endl;
  std::cout << std::endl;
  std::cout << "Please choose an option:" << std::endl;
  std::cout << "0. Logout" << std::endl;
  std::cout << "1. View my account" << std::endl;
  std::cout << "2. View active auction" << std::endl;
  std::cout << "3. Top up credit" << std::endl;
  std::cout << "4. Account overview." << std::endl;
  std::cout << "5. View all transactions." << std::endl;
  std::cout << "6. Change password." << std::endl;
  std::cout << "7. Search and filter items by name." << std::endl;
  std::cout << "8. Search and filter items by credit points." << std::endl;
  std::cout << "9. Search and filter items by category." << std::endl;
  return Dashboard::handleMemberMenu(false);
}

void Dashboard::handleMemberMenu(bool clear = true)
{
  if (clear)
    clearing();
  std::cout << "Enter your choice: ";
  int choice;
  std::cin >> choice;

  // Check if choice is integer
  if (std::cin.fail())
  {
    std::cin.clear();
    std::cin.ignore();
    std::cout << "Invalid choice. Please try again." << std::endl;
    // waiting for 3 seconds
    waiting(3);
    return Dashboard::displayMemberMenu();
  }

  switch (choice)
  {
  case 0:
  {
    std::cout << "Logging out..." << std::endl;
    this->member = nullptr;
    this->currentRole = "";
    return Dashboard::displayMainMenu();
  }

  case 1:
  {
    clearing();
    std::cout << "====================================" << std::endl;
    std::cout << "          Account detailed          " << std::endl;
    std::cout << "====================================" << std::endl
              << std::endl;
    std::cout << "Member ID: " << this->member->getMemberID() << std::endl;
    std::cout << "Full name: " << this->member->getFullname() << std::endl;
    std::cout << "Phone number: " << this->member->getPhoneNumber()
              << std::endl;
    std::cout << "Email: " << this->member->getEmail() << std::endl;

    if (this->member->getIDNumber().substr(0, 2) == "P-")
      std::cout << "Passport number: " << this->member->getIDNumber().substr(2)
                << std::endl;
    else
      std::cout << "Citizen ID: " << this->member->getIDNumber().substr(2) << std::endl;

    std::cout << "Credit: " << this->member->getCredit() << std::endl;
    std::cout << "Rating score: " << this->member->getRating() << std::endl;
    std::cout << std::endl
              << "Return to member menu in 10 seconds..." << std::endl;
    // waiting 10 seconds
    waiting(10);
    return Dashboard::displayMemberMenu();
  }

  case 2:
  {
    return Dashboard::displayMemberAuctionMenu();
  }

  case 3:
  {
    clearing();
    std::cout << "====================================" << std::endl;
    std::cout << "          Top up credit             " << std::endl;
    std::cout << "====================================" << std::endl;
    std::cout << std::endl;

    float credit;
    std::cout << "Enter credit amount: ";
    std::cin >> credit;

    this->member->setCredit(credit);
    this->member->save();
    std::cout << "Credit topped up successfully!" << std::endl;

    // waiting for 3 seconds
    waiting(3);
    break;
  }

  case 4:
  {
    clearing();
    std::cout << "====================================" << std::endl;
    std::cout << "          Account overview          " << std::endl;
    std::cout << "====================================" << std::endl;
    std::cout << std::endl;

    Database database;
    std::vector<Item> activeItems;
    for (Item &item : Database().getAllItems())
    {
      if (database.getAuctionByID(item.getAuctionID())->getEndTime() == 0 &&
          item.getSellerID() == this->member->getMemberID())
      {
        activeItems.push_back(item);
      }
    }
    std::cout << "Active item listings: " << activeItems.size() << std::endl;

    std::vector<Bid> activeBid;
    for (Bid &bid : Database().getAllBids())
    {
      Auction auction = *database.getAuctionByID(
          database.getItemByID(bid.getItemID())->getAuctionID());
      Item item = *database.getItemByID(bid.getItemID());

      if (auction.getEndTime() == 0 && // Auction is still active
          bid.getMemberID() ==
              this->member->getMemberID() && // Bidder is
                                             // current member
          item.getCurrentBidAmount() == bid.getBidAmount())
      { // Bid is
        // highest
        activeBid.push_back(bid);
      }
    }
    std::cout << "Active bids: " << activeBid.size() << std::endl;

    std::vector<Transaction> boughtTransaction;
    for (Transaction &transaction : Database().getAllTransactions())
    {
      if (transaction.getBuyerID() == this->member->getMemberID())
      {
        boughtTransaction.push_back(transaction);
      }
    }
    std::cout << "Total bought items: " << boughtTransaction.size()
              << std::endl;

    std::vector<Transaction> soldTransaction;
    for (Transaction &transaction : Database().getAllTransactions())
    {
      if (transaction.getSellerID() == this->member->getMemberID())
      {
        soldTransaction.push_back(transaction);
      }
    }
    std::cout << "Total sold items: " << soldTransaction.size() << std::endl;

    std::cout << "Account balance: " << this->member->getCredit() << " CP."
              << std::endl;

    std::cout << std::endl
              << "----------" << std::endl;
    std::cout << "Your active item listings:" << std::endl;
    int index = 1;
    for (Item &item : activeItems)
    {
      std::cout << index << ". Name: " << item.getItemName()
                << ", Category: " << item.getCategory()
                << ", Current bid: " << item.getCurrentBidAmount() << " CP."
                << std::endl;
      index++;
    }
    if (activeItems.size() == 0)
    {
      std::cout << "No active item listings." << std::endl;
    }

    std::cout << std::endl
              << "----------" << std::endl;
    std::cout << "Your active bids (bids that leading the item):"
              << std::endl;
    index = 1;
    for (Bid &bid : activeBid)
    {
      Item item = *database.getItemByID(bid.getItemID());
      std::cout << index << ". Item: " << item.getItemName()
                << ", Category: " << item.getCategory()
                << ", Bid: " << bid.getBidAmount() << " CP." << std::endl;
      index++;
    }
    if (activeBid.size() == 0)
    {
      std::cout << "No active bids." << std::endl;
    }

    std::cout << std::endl
              << "----------" << std::endl;
    std::cout << "Your bought items:" << std::endl;
    index = 1;
    for (Transaction &transaction : boughtTransaction)
    {
      Item item = *database.getItemByID(transaction.getItemID());
      std::cout << index << ". Item: " << item.getItemName()
                << ", Category: " << item.getCategory()
                << ", Price: " << item.getCurrentBidAmount() << " CP."
                << std::endl;
      index++;
    }
    if (boughtTransaction.size() == 0)
    {
      std::cout << "No bought items." << std::endl;
    }

    std::cout << std::endl
              << "----------" << std::endl;
    std::cout << "Your sold items:" << std::endl;
    index = 1;
    for (Transaction &transaction : soldTransaction)
    {
      Item item = *database.getItemByID(transaction.getItemID());
      std::cout << index << ". Item: " << item.getItemName()
                << ", Category: " << item.getCategory()
                << ", Price: " << item.getCurrentBidAmount() << " CP."
                << std::endl;
      index++;
    }
    if (soldTransaction.size() == 0)
    {
      std::cout << "No sold items." << std::endl;
    }

    int choice;
    std::cout << std::endl
              << "0. Back to member menu." << std::endl;
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    // Check if choice is integer
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore();
      std::cout << "Invalid choice. Please try again." << std::endl;
      // waiting for 3 seconds
      waiting(3);
      return Dashboard::displayMemberMenu();
    }

    if (choice == 0)
    {
      return Dashboard::displayMemberMenu();
    }
    else
    {
      std::cout << "Invalid choice. Please try again." << std::endl;
      // waiting for 3 seconds
      waiting(3);
      return Dashboard::displayMemberMenu();
    }
  }

  case 5:
  {
    clearing();
    std::cout << "====================================" << std::endl;
    std::cout << "        Account transactions        " << std::endl;
    std::cout << "====================================" << std::endl
              << std::endl;
    std::cout << "0. Back to member menu." << std::endl;

    Database database;
    // Update member instance
    this->member = database.getMemberByID(this->member->getMemberID());

    std::vector<Transaction> filteredTransactions;
    // Get all transactions that this member is involved in
    for (Transaction &transaction : Database().getAllTransactions())
    {
      if (transaction.getBuyerID() == this->member->getMemberID() ||
          transaction.getSellerID() == this->member->getMemberID())
      {
        filteredTransactions.push_back(transaction);
      }
    }

    int index = 1;
    for (Transaction &transaction : filteredTransactions)
    {
      Item item = *database.getItemByID(transaction.getItemID());
      if (transaction.getBuyerID() == this->member->getMemberID())
      {
        std::cout << index << ". Bought " << item.getItemName() << " with "
                  << item.getCurrentBidAmount() << " CP." << std::endl;
      }
      else
      {
        std::cout << index << ". Sold " << item.getItemName() << " with "
                  << item.getCurrentBidAmount() << " CP." << std::endl;
      }
      index++;
    }

    int choice;
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    // Check if choice is integer
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore();
      std::cout << "Invalid choice. Please try again." << std::endl;
      // waiting for 3 seconds
      waiting(3);
      return Dashboard::displayMemberMenu();
    }

    switch (choice)
    {
    case 0:
    {
      return Dashboard::displayMemberMenu();
    }

    default:
    {
      // Check if choice is within the range of transactions
      if (choice > 0 && choice <= filteredTransactions.size())
      {
        return Dashboard::displayTransactionDetailedMenu(
            &filteredTransactions[choice - 1]);
      }
      else
      {
        std::cout << "Invalid choice. Please try again." << std::endl;
        // waiting for 3 seconds
        waiting(3);
        return Dashboard::displayMemberMenu();
      }
    }
    }
  }

  case 6:
  {
    clearing();
    std::cout << "====================================" << std::endl;
    std::cout << "          Change password           " << std::endl;
    std::cout << "====================================" << std::endl;
    std::cout << std::endl;

    std::cout << "Enter your old password: ";
    std::string oldPassword;
    std::cin >> oldPassword;
    std::cout << "Enter your new password: ";
    std::string newPassword;
    std::cin >> newPassword;

    Database database;
    User *user = database.getUserByID(this->member->getUserID());
    if (!user->checkPassword(oldPassword))
    {
      std::cout << "Old password is incorrect. Please try again." << std::endl;
      // waiting for 3 seconds
      waiting(3);
      return Dashboard::displayMemberMenu();
    }
    else
    {
      user->setPassword(newPassword);
      user->save();
      std::cout << "Password changed successfully!" << std::endl;
      // waiting for 3 seconds
      waiting(3);
      return Dashboard::displayMemberMenu();
    }
  }

  case 7:
  {
    clearing();
    std::cout << "====================================" << std::endl;
    std::cout << "       Search and filter items       " << std::endl;
    std::cout << "====================================" << std::endl;
    std::cout << std::endl;

    std::cout << "Enter search keyword: ";
    std::string keyword;
    std::cin >> keyword;

    std::cout << std::endl
              << "0. Back to member menu." << std::endl;
    std::vector<Item> filteredItems;
    for (Item &item : Database().getAllItems())
    {
      if (item.getItemName().find(keyword) != std::string::npos && Database().getAuctionByID(item.getAuctionID())->getEndTime() == 0)
      {
        filteredItems.push_back(item);
      }
    }
    if (filteredItems.size() == 0)
    {
      std::cout << "No items found." << std::endl;
      // waiting for 3 seconds
    }

    int index = 1;
    for (Item &item : filteredItems)
    {
      std::cout << index << ". Name: " << item.getItemName()
                << ", Category: " << item.getCategory()
                << ", Current bid: " << item.getCurrentBidAmount() << " CP."
                << std::endl;
      index++;
    }

    int choice;
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    // Check if choice is integer
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore();
      std::cout << "Invalid choice. Please try again." << std::endl;
      // waiting for 3 seconds
      waiting(3);
      return Dashboard::displayMemberMenu();
    }

    switch (choice)
    {
    case 0:
    {
      return Dashboard::displayMemberMenu();
    }

    default:
    {
      // Check if choice is within the range of filtered items
      if (choice > 0 && choice <= filteredItems.size())
      {
        return Dashboard::displayItemsDetailMenu(&filteredItems[choice - 1], Database().getAuctionByID(filteredItems[choice - 1].getAuctionID()));
      }
      else
      {
        std::cout << "Invalid choice. Please try again." << std::endl;
        // waiting for 3 seconds
        waiting(3);
        return Dashboard::displayMemberMenu();
      }
    }
    }
  }

  case 8:
  {
    clearing();
    std::cout << "====================================" << std::endl;
    std::cout << "       Search and filter items       " << std::endl;
    std::cout << "====================================" << std::endl;
    std::cout << std::endl;

    std::cout << "Enter minimum credit points: ";
    float minCredit;
    std::cin >> minCredit;
    std::cout << "Enter maximum credit points: ";
    float maxCredit;
    std::cin >> maxCredit;

    std::cout << std::endl
              << "0. Back to member menu." << std::endl;
    std::vector<Item> filteredItems;
    for (Item &item : Database().getAllItems())
    {
      if ((item.getCurrentBidAmount() >= minCredit || item.getCurrentBidAmount() == 0) &&
          (item.getCurrentBidAmount() <= maxCredit || item.getCurrentBidAmount() == 0) && Database().getAuctionByID(item.getAuctionID())->getEndTime() == 0)
      {
        filteredItems.push_back(item);
      }
    }
    if (filteredItems.size() == 0)
    {
      std::cout << "No items found." << std::endl;
    }

    int index = 1;
    for (Item &item : filteredItems)
    {
      std::cout << index << ". Name: " << item.getItemName()
                << ", Category: " << item.getCategory()
                << ", Current bid: " << item.getCurrentBidAmount() << " CP."
                << std::endl;
      index++;
    }

    int choice;
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    // Check if choice is integer
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore();
      std::cout << "Invalid choice. Please try again." << std::endl;
      // waiting for 3 seconds
      waiting(3);
      return Dashboard::displayMemberMenu();
    }

    switch (choice)
    {
    case 0:
    {
      return Dashboard::displayMemberMenu();
    }

    default:
    {
      // Check if choice is within the range of filtered items
      if (choice > 0 && choice <= filteredItems.size())
      {
        return Dashboard::displayItemsDetailMenu(&filteredItems[choice - 1], Database().getAuctionByID(filteredItems[choice - 1].getAuctionID()));
      }
      else
      {
        std::cout << "Invalid choice. Please try again." << std::endl;
        // waiting for 3 seconds
        waiting(3);
        return Dashboard::displayMemberMenu();
      }
    }
    }
  }

  case 9:
  {
    clearing();
    std::cout << "====================================" << std::endl;
    std::cout << "       Search and filter items       " << std::endl;
    std::cout << "====================================" << std::endl;
    std::cout << std::endl;

    std::cout << "Enter category: ";
    std::string category;
    std::cin >> category;

    std::cout << std::endl
              << "0. Back to member menu." << std::endl;
    std::vector<Item> filteredItems;
    for (Item &item : Database().getAllItems())
    {
      if (item.getCategory().find(category) != std::string::npos && Database().getAuctionByID(item.getAuctionID())->getEndTime() == 0)
      {
        filteredItems.push_back(item);
      }
    }

    int index = 1;
    for (Item &item : filteredItems)
    {
      std::cout << index << ". Name: " << item.getItemName()
                << ", Category: " << item.getCategory()
                << ", Current bid: " << item.getCurrentBidAmount() << " CP."
                << std::endl;
      index++;
    }

    int choice;
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    // Check if choice is integer
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore();
      std::cout << "Invalid choice. Please try again." << std::endl;
      // waiting for 3 seconds
      waiting(3);
      return Dashboard::displayMemberMenu();
    }

    switch (choice)
    {
    case 0:
    {
      return Dashboard::displayMemberMenu();
    }

    default:
    {
      // Check if choice is within the range of filtered items
      if (choice > 0 && choice <= filteredItems.size())
      {
        return Dashboard::displayItemsDetailMenu(&filteredItems[choice - 1], Database().getAuctionByID(filteredItems[choice - 1].getAuctionID()));
      }
      else
      {
        std::cout << "Invalid choice. Please try again." << std::endl;
        // waiting for 3 seconds
        waiting(3);
        return Dashboard::displayMemberMenu();
      }
    }
    }
  }

  default:
  {
    std::cout << "Invalid choice. Please try again." << std::endl;
    // waiting for 3 seconds
    waiting(3);
    break;
  }
  }
  return Dashboard::displayMemberMenu();
}