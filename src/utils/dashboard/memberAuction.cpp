#include <stdlib.h>
#include <string>
#include <ctime>

#include "../../libs/Admin.h"
#include "../../libs/Auction.h"
#include "../../libs/Dashboard.h"
#include "../../libs/Database.h"
#include "../../libs/Member.h"
#include "../../libs/User.h"
#include "../..//libs/waiting.h"

void Dashboard::displayMemberAuctionMenu()
{
  std::system("clear");

  Database database;
  std::vector<Auction> auctions = database.getAllAuctions();
  std::vector<Auction> activeAuctions;
  for (Auction &auction : auctions)
  {
    if (auction.getEndTime() == -1)
      activeAuctions.push_back(auction);
  }

  std::cout << "====================================" << std::endl;
  std::cout << "          Active auctions           " << std::endl;
  std::cout << "====================================" << std::endl
            << std::endl;
  std::cout << "0. Back to member menu." << std::endl;
  for (int index = 1; index <= activeAuctions.size(); index++)
  {
    std::cout << index << ". View "
              << activeAuctions.at(index - 1).getAuctionName() << std::endl;
  }

  return Dashboard::handleMemberAuctionMenu(false);
}

void Dashboard::handleMemberAuctionMenu(bool clear = true)
{
  if (clear)
    std::system("clear");
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
    sleep(3);
    return Dashboard::displayMemberAuctionMenu();
  }

  switch (choice)
  {
  case 0:
  {
    return Dashboard::displayMemberMenu();
  }

  default:
  {
    // Check if choice is integer and within the range of auctions
    Database database;
    std::vector<Auction> auctions = database.getAllAuctions();
    std::vector<Auction> activeAuctions;
    for (Auction &auction : auctions)
    {
      if (auction.getEndTime() == -1)
        activeAuctions.push_back(auction);
    }

    if (choice < 0 || choice > activeAuctions.size())
    {
      std::cout << "Invalid choice. Please try again." << std::endl;
      // waiting for 3 seconds
      sleep(3);
      return Dashboard::displayMemberAuctionMenu();
    }
    else
    {
      Auction auction = activeAuctions.at(choice - 1);
      return Dashboard::displayMemberAuctionDetailMenu(&auction);
    }
  }
  }
  return Dashboard::displayMemberAuctionMenu();
}

void Dashboard::displayMemberAuctionDetailMenu(Auction *auction)
{
  std::system("clear");
  std::cout << "=====================================" << std::endl;
  std::cout << "    Auction Detail Menu for Member   " << std::endl;
  std::cout << "=====================================" << std::endl;
  std::cout << std::endl;

  std::cout << "Auction ID: " << auction->getAuctionID() << std::endl;
  std::cout << "Auction name: " << auction->getAuctionName() << std::endl;

  time_t startTimeT = auction->getStartTime();
  time_t endTimeT = auction->getEndTime();
  std::string startTime = std::string(ctime(&startTimeT));
  std::string endTime = std::string(ctime(&endTimeT));
  startTime.pop_back();
  endTime.pop_back();
  std::cout << "Start time: "
            << (auction->getStartTime() == -1 ? "Not yet" : startTime)
            << std::endl;
  std::cout << "End time: "
            << (auction->getEndTime() == -1 ? "Not yet" : endTime) << std::endl;
  std::cout << std::endl;

  std::cout << "Please choose an option:" << std::endl;
  std::cout << "0. Back to member auction menu." << std::endl;
  std::cout << "1. View auction items." << std::endl;
  std::cout << "2. Sell items." << std::endl;
  return Dashboard::handleMemberAuctionDetailMenu(auction, false);
}

void Dashboard::handleMemberAuctionDetailMenu(Auction *auction,
                                              bool clear = true)
{
  if (clear)
    std::system("clear");
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
    sleep(3);
    return Dashboard::displayMemberAuctionDetailMenu(auction);
  }

  switch (choice)
  {
  case 0:
  {
    return Dashboard::displayMemberAuctionMenu();
  }

  case 1:
  {
    return Dashboard::displayItemsMenu(auction);
  }

  case 2:
  {
    std::system("clear");
    std::cout << "=====================================" << std::endl;
    std::cout << "       Selling items in auction      " << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << std::endl;

    std::string name;
    std::cout << "Enter item name: ";
    getline(std::cin >> std::ws, name);

    std::string description;
    std::cout << "Enter item description: ";
    getline(std::cin >> std::ws, description);

    std::string category;
    std::cout << "Enter item category: ";
    getline(std::cin >> std::ws, category);

    float startingBidAmount;
    std::cout << "Enter starting bid amount: ";
    std::cin >> startingBidAmount;

    float bidIncrement;
    std::cout << "Enter bid increment: ";
    std::cin >> bidIncrement;

    float minBuyerRating;
    std::cout << "Enter minimum buyer rating: ";
    std::cin >> minBuyerRating;

    Item item(name, category, description, *this->member, startingBidAmount,
              bidIncrement, minBuyerRating, auction->getAuctionID());
    item.save();
    std::cout << "Item added successfully!" << std::endl;

    // waiting for 3 seconds
    sleep(3);
    return Dashboard::displayMemberAuctionDetailMenu(auction);
  }

  default:
  {
    std::cout << "Invalid choice. Please try again." << std::endl;
    // waiting for 3 seconds
    sleep(3);
    break;
  }
  }
  return Dashboard::displayMemberAuctionDetailMenu(auction);
}
