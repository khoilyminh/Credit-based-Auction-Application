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

void Dashboard::displayMemberMenu() {
  std::system("clear");
  std::cout << "====================================" << std::endl;
  std::cout << "            Member Menu             " << std::endl;
  std::cout << "====================================" << std::endl;
  std::cout << std::endl;
  std::cout << "Please choose an option:" << std::endl;
  std::cout << "0. Logout" << std::endl;
  std::cout << "1. View my account" << std::endl;
  std::cout << "2. View active auction" << std::endl;
  std::cout << "3. Top up credit" << std::endl;
  return Dashboard::handleMemberMenu(false);
}

void Dashboard::handleMemberMenu(bool clear = true) {
  if (clear) std::system("clear");
  std::cout << "Enter your choice: ";
  int choice;
  std::cin >> choice;

  // Check if choice is integer
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore();
    std::cout << "Invalid choice. Please try again." << std::endl;
    // Wait for 3 seconds
    sleep(3);
    return Dashboard::displayMemberMenu();
  }

  switch (choice) {
    case 0: {
      std::cout << "Logging out..." << std::endl;
      this->member = nullptr;
      this->currentRole = "";
      return Dashboard::displayMainMenu();
    }

    case 1: {
      std::system("clear");
      std::cout << "====================================" << std::endl;
      std::cout << "          Account detailed          " << std::endl;
      std::cout << "====================================" << std::endl
                << std::endl;
      std::cout << "Member ID: " << this->member->getMemberID() << std::endl;
      std::cout << "Full name: " << this->member->getFullname() << std::endl;
      std::cout << "Phone number: " << this->member->getPhoneNumber()
                << std::endl;
      std::cout << "Email: " << this->member->getEmail() << std::endl;
      std::cout << "Credit: " << this->member->getCredit() << std::endl;
      std::cout << "Rating score: " << this->member->getRating() << std::endl;
      std::cout << std::endl
                << "Return to member menu in 10 seconds..." << std::endl;
      // Wait 10 seconds
      sleep(10);
      return Dashboard::displayMemberMenu();
    }

    case 2: {
      return Dashboard::displayMemberAuctionMenu();
    }

    case 3: {
      std::system("clear");
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
  return Dashboard::displayMemberMenu();
}