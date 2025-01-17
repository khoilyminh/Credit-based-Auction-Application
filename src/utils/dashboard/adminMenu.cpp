#include <stdlib.h>
#include <iomanip>
#include <string>
#include <ctime>

#include "../../libs/Admin.h"
#include "../../libs/Auction.h"
#include "../../libs/Dashboard.h"
#include "../../libs/Database.h"
#include "../../libs/Member.h"
#include "../..//libs/waiting.h"
#include "../../libs/clearing.h"

void Dashboard::displayAdminMenu()
{
  clearing();
  std::cout << "====================================" << std::endl;
  std::cout << "         Administrator Menu         " << std::endl;
  std::cout << "====================================" << std::endl;
  std::cout << std::endl;
  std::cout << "Please choose an option:" << std::endl;
  std::cout << "0. Logout" << std::endl;
  std::cout << "1. Create new auction" << std::endl;
  std::cout << "2. View all auctions" << std::endl;
  std::cout << "3. View all members." << std::endl;
  std::cout << "4. View all items." << std::endl;
  return Dashboard::handleAdminMenu(false);
}

void Dashboard::handleAdminMenu(bool clear = true)
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
    return Dashboard::displayAdminMenu();
  }

  switch (choice)
  {
  case 1:
  {
    clearing();
    std::cout << "Creating new auction..." << std::endl;

    std::string name;
    std::cout << "Enter auction name: ";
    getline(std::cin >> std::ws, name);

    Auction auction(name);
    auction.save();

    std::cout << "Auction created successfully!" << std::endl;
    std::cout << auction.toString() << std::endl;

    // waiting for 3 seconds
    waiting(3);
    break;
  }

  case 2:
  {
    return Dashboard::displayAdminAuctionMenu();
  }

  case 3:
  {
    clearing();
    std::cout << "====================================" << std::endl;
    std::cout << "           List of members          " << std::endl;
    std::cout << "====================================" << std::endl;
    std::cout << std::endl;

    int index = 1;
    Database database;
    for (Member &member : database.getAllMembers())
    {
      std::cout << std::to_string(index) << ". "
                << "Fullname: " << member.getFullname()
                << ", Email: " << member.getEmail()
                << ", Phone: " << member.getPhoneNumber()
                << ", Rating: " << member.getRating()
                << ", Credit point: " << member.getCredit() << std::endl;
      index++;
    }

    std::cout << std::endl;
    std::cout << "Please choose an option:" << std::endl;
    std::cout << "0. Back to administrator menu." << std::endl;
    int choice;
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    if (choice != 0)
    {
      std::cout << "Invalid choice. Please try again." << std::endl;
      // waiting for 3 seconds
      waiting(3);
    }
    return Dashboard::displayAdminMenu();
  }

  case 4:
  {
    clearing();
    std::cout << "====================================" << std::endl;
    std::cout << "            List of items           " << std::endl;
    std::cout << "====================================" << std::endl;
    std::cout << std::endl;

    int index = 1;
    Database database;
    for (Item &item : database.getAllItems())
    {
      std::cout
          << std::to_string(index) << ". "
          << "Name: " << item.getItemName()
          << ", Description: " << item.getDescription()
          << ", Category: " << item.getCategory()
          << ", Starting price: " << item.getStartingBidAmount()
          << ", Current price: " << item.getCurrentBidAmount()
          << ", Auction: "
          << database.getAuctionByID(item.getAuctionID())->getAuctionName()
          << (database.getTransactionsByItemID(item.getItemID()).size() > 0
                  ? ", Sold"
                  : ", Unsold")
          << std::endl
          << std::endl;
      index++;
    }

    std::cout << std::endl;
    std::cout << "Please choose an option:" << std::endl;
    std::cout << "0. Back to administrator menu." << std::endl;
    int choice;
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    if (choice != 0)
    {
      std::cout << "Invalid choice. Please try again." << std::endl;
      // waiting for 3 seconds
      waiting(3);
    }
    return Dashboard::displayAdminMenu();
  }

  case 0:
  {
    std::cout << "Logging out..." << std::endl;
    this->admin = nullptr;
    this->currentRole = "";
    return Dashboard::displayMainMenu();
  }

  default:
  {
    std::cout << "Invalid choice. Please try again." << std::endl;
    // waiting for 3 seconds
    waiting(3);
    break;
  }
  }
  return Dashboard::displayAdminMenu();
}