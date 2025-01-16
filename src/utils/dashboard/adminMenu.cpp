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

void Dashboard::displayAdminMenu() {
  std::system("clear");
  std::cout << "====================================" << std::endl;
  std::cout << "         Administrator Menu         " << std::endl;
  std::cout << "====================================" << std::endl;
  std::cout << std::endl;
  std::cout << "Please choose an option:" << std::endl;
  std::cout << "0. Logout" << std::endl;
  std::cout << "1. Create new auction" << std::endl;
  std::cout << "2. View all auctions" << std::endl;
  return Dashboard::handleAdminMenu(false);
}

void Dashboard::handleAdminMenu(bool clear = true) {
  if (clear) std::system("clear");
  std::cout << "Enter your choice: ";
  int choice;
  std::cin >> choice;

  switch (choice) {
    case 1: {
      std::system("clear");
      std::cout << "Creating new auction..." << std::endl;

      std::string name;
      std::cout << "Enter auction name: ";
      getline(std::cin >> std::ws, name);

      Auction auction(name);
      auction.save();

      std::cout << "Auction created successfully!" << std::endl;
      std::cout << auction.toString() << std::endl;

      // Wait for 3 seconds
      sleep(3);
      break;
    }

    case 2: {
      return Dashboard::displayAdminAuctionMenu();
    }

    case 0: {
      std::cout << "Logging out..." << std::endl;
      this->admin = nullptr;
      this->currentRole = "";
      return Dashboard::displayMainMenu();
    }

    default: {
      std::cout << "Invalid choice. Please try again." << std::endl;
      // Wait for 3 seconds
      sleep(3);
      break;
    }
  }
  return Dashboard::displayAdminMenu();
}