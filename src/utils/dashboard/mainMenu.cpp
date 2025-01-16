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

void Dashboard::displayMainMenu() {
  std::system("clear");
  std::cout << "EEET2482/COSC2082 GROUP ASSIGNMENT" << std::endl;
  std::cout << "Semester 3 2024" << std::endl;
  std::cout << "AUCTION APPLICATION" << std::endl;
  std::cout << std::endl;
  std::cout << "Instructor: Dr Ling Huo Chong" << std::endl;
  std::cout << "Group: 8" << std::endl;
  std::cout << "S4032825, Dinh Ngoc Hoang Cuong" << std::endl;
  std::cout << "S3989037, Ly Minh Khoi" << std::endl;
  std::cout << "S4040506, Nguyen Phuong Anh" << std::endl;
  std::cout << "S4014896, Nguyen Duc Trung" << std::endl;
  std::cout << std::endl;
  std::cout << "====================================" << std::endl;
  std::cout << "           Welcome to the           " << std::endl;
  std::cout << "  Credit-Based Auction Application        " << std::endl;
  std::cout << "====================================" << std::endl;
  std::cout << std::endl;
  std::cout << "Please choose an option:" << std::endl;
  std::cout << "1. Continue as Guest" << std::endl;
  std::cout << "2. Login as Member" << std::endl;
  std::cout << "3. Login as Admin" << std::endl;
  std::cout << "4. Sign up as Member" << std::endl;
  std::cout << "5. Sign up as Admin" << std::endl;
  std::cout << "6. Exit" << std::endl;
  return Dashboard::handleMainMenu(false);
}

void Dashboard::handleMainMenu(bool clear = true) {
  if (clear) std::system("clear");

  int choice;
  std::cout << "Enter your choice: ";
  std::cin >> choice;

  switch (choice) {
    case 1: {
      std::cout << "Continuing as Guest..." << std::endl;
      // Add logic for guest functionality
      break;
    }

    case 2: {
      std::system("clear");
      std::cout << "Logging in as Member..." << std::endl;
      std::string username, password;
      std::cout << "Enter username: ";
      std::cin >> username;
      std::cout << "Enter password: ";
      std::cin >> password;

      User user;
      try {
        user.checkAuthentication(username, password);
      } catch (const std::invalid_argument &e) {
        std::cout << "Error: " << e.what() << std::endl;
        // Wait for 3 seconds
        sleep(3);
        return Dashboard::displayMainMenu();
      }

      Member member;
      try {
        member.findMemberByUser(user);
      } catch (const std::invalid_argument &e) {
        std::cout << "Error: " << e.what() << std::endl;
        // Wait for 3 seconds
        sleep(3);
        return Dashboard::displayMainMenu();
      }
      std::cout << "Welcome back, " << member.getFullname() << "!" << std::endl;
      this->member = &member;
      this->currentRole = "Member";
      return Dashboard::displayMemberMenu();
    }

    case 3: {
      std::system("clear");
      std::cout << "Logging in as Admin..." << std::endl;

      std::string username, password;
      std::cout << "Enter username: ";
      std::cin >> username;
      std::cout << "Enter password: ";
      std::cin >> password;

      User user;
      try {
        user.checkAuthentication(username, password);
      } catch (const std::invalid_argument &e) {
        std::cout << "Error: " << e.what() << std::endl;
        // Wait for 3 seconds
        sleep(3);
        return Dashboard::displayMainMenu();
      }

      Admin admin;
      try {
        admin.getAdminByUser(user);
      } catch (const std::invalid_argument &e) {
        std::cout << "Error: " << e.what() << std::endl;
        // Wait for 3 seconds
        sleep(3);
        return Dashboard::displayMainMenu();
      }

      std::cout << "Welcome back " << user.getUsername() << "!" << std::endl;
      this->admin = &admin;
      this->currentRole = "Admin";

      return Dashboard::displayAdminMenu();
    }

    case 4: {
      std::system("clear");
      User user;
      try {
        std::cout << "Signing up as Member..." << std::endl;
        // Create a new user
        std::string username, password;
        std::cout << "Enter username: ";
        std::cin >> username;
        std::cout << "Enter password: ";
        std::cin >> password;
        user = User(username, password);
        user.save();
      } catch (const std::invalid_argument &e) {
        std::cout << "Error: " << e.what() << std::endl;
        // Wait for 3 seconds
        sleep(3);
        return Dashboard::displayMainMenu();
      }
      try {
        // Create a new member
        std::string fullname, phoneNumber, email;
        // Get whole line including spaces
        std::cout << "Enter full name: ";
        getline(std::cin >> std::ws, fullname);
        std::cout << "Enter phone number: ";
        std::cin >> phoneNumber;
        std::cout << "Enter email: ";
        std::cin >> email;
        Member member = Member(fullname, phoneNumber, email, user);
        member.save();
      } catch (const std::invalid_argument &e) {
        std::cout << "Error: " << e.what() << std::endl;
        // Wait for 3 seconds
        sleep(3);
        return Dashboard::displayMainMenu();
      }
      return Dashboard::displayMainMenu();
    }

    case 5: {
      std::system("clear");
      std::cout << "Signing up as Admin..." << std::endl;
      User user;
      try {
        // Create a new user
        std::string username, password;
        std::cout << "Enter username: ";
        std::cin >> username;
        std::cout << "Enter password: ";
        std::cin >> password;
        user = User(username, password);
        user.save();
      } catch (const std::invalid_argument &e) {
        std::cout << "Error: " << e.what() << std::endl;
        // Wait for 3 seconds
        sleep(3);
        return Dashboard::displayMainMenu();
      }
      try {
        Admin admin = Admin(user);
        admin.save();
      } catch (const std::invalid_argument &e) {
        std::cout << "Error: " << e.what() << std::endl;
        // Wait for 3 seconds
        sleep(3);
        return Dashboard::displayMainMenu();
      }
      std::cout << "Admin account created successfully!" << std::endl;
      // Wait for 3 seconds
      sleep(3);
      return Dashboard::displayMainMenu();
    }

    case 6: {
      std::cout << "Exiting the application." << std::endl;
      exit(0);
    }

    default: {
      std::cout << "Invalid choice. Please try again." << std::endl;
      // Wait for 3 seconds
      sleep(3);
      return Dashboard::displayMainMenu();  // Prompt again for valid input
    }
  }
}