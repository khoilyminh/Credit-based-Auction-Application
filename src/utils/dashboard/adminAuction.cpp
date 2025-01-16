#include <stdlib.h>

#include <string>
// #include <windows.h> // For Windows OS
#include <unistd.h>  // For Unix-based OS

#include <ctime>

#include "../../libs/Admin.h"
#include "../../libs/Auction.h"
#include "../../libs/Dashboard.h"
#include "../../libs/Database.h"
#include "../../libs/Member.h"
#include "../../libs/User.h"

void Dashboard::displayAdminAuctionMenu() {
  std::system("clear");
  std::cout << "====================================" << std::endl;
  std::cout << "  Auctions Menu for Administrator   " << std::endl;
  std::cout << "====================================" << std::endl;
  std::cout << std::endl;

  std::cout << "0. Back to admin menu." << std::endl;

  Database database;
  int index = 1;
  for (Auction &auction : database.getAllAuctions()) {
    std::cout << index << ". " << auction.getAuctionName() << std::endl;
    index++;
  }

  return Dashboard::handleAdminAuctionMenu(false);
}

void Dashboard::handleAdminAuctionMenu(bool clear = true) {
  if (clear) std::system("clear");
  std::cout << "Enter your choice: ";
  int choice;
  std::cin >> choice;

  switch (choice) {
    case 0: {
      return Dashboard::displayAdminMenu();
    }

    default: {
      // Check if choice is integer and within the range of auctions
      Database database;
      if (choice < 0 || choice > database.getAllAuctions().size()) {
        std::cout << "Invalid choice. Please try again." << std::endl;
        // Wait for 3 seconds
        sleep(3);
        return Dashboard::displayAdminAuctionMenu();
      } else {
        Auction auction = database.getAllAuctions().at(choice - 1);
        return Dashboard::displayAdminAuctionDetailMenu(&auction);
      }
    }
  }
  return Dashboard::displayAdminAuctionMenu();
}

void Dashboard::displayAdminAuctionDetailMenu(Auction *auction) {
  std::system("clear");
  std::cout << "=====================================" << std::endl;
  std::cout << "Auction Detail Menu for Administrator" << std::endl;
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
  std::cout << "0. Back to admin auction menu." << std::endl;
  std::cout << "1. Start auction." << std::endl;
  std::cout << "2. End auction." << std::endl;

  return Dashboard::handleAdminAuctionDetailMenu(auction, false);
}

void Dashboard::handleAdminAuctionDetailMenu(Auction *auction,
                                             bool clear = true) {
  if (clear) std::system("clear");
  std::cout << "Enter your choice: ";
  int choice;
  std::cin >> choice;

  switch (choice) {
    case 0: {
      return Dashboard::displayAdminAuctionMenu();
    }

    case 1: {
      try {
        auction->startAuction();
        auction->save();
      } catch (const std::invalid_argument &e) {
        std::cout << "Error: " << e.what() << std::endl;
        // Wait for 3 seconds
        sleep(3);
        return Dashboard::displayAdminAuctionDetailMenu(auction);
      }
      std::cout << "Auction started successfully!" << std::endl;
      // Wait for 3 seconds
      sleep(3);
      break;
    }

    case 2: {
      try {
        auction->endAuction();
        auction->save();
      } catch (const std::invalid_argument &e) {
        std::cout << "Error: " << e.what() << std::endl;
        // Wait for 3 seconds
        sleep(3);
        return Dashboard::displayAdminAuctionDetailMenu(auction);
      }
      std::cout << "Auction ended successfully!" << std::endl;
      // Wait for 3 seconds
      sleep(3);
      break;
    }

    default: {
      std::cout << "Invalid choice. Please try again." << std::endl;
      // Wait for 3 seconds
      sleep(3);
      break;
    }
  }
  return Dashboard::displayAdminAuctionDetailMenu(auction);
}