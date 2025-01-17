#include <stdlib.h>
#include <string>
#include <ctime>

#include "../../libs/Admin.h"
#include "../../libs/Dashboard.h"
#include "../../libs/Database.h"
#include "../../libs/Member.h"
#include "../../libs/User.h"
#include "../..//libs/waiting.h"
#include "../../libs/clearing.h"

void Dashboard::displayMainMenu()
{
  clearing();
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

void Dashboard::handleMainMenu(bool clear = true)
{
  if (clear)
    clearing();

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
    return Dashboard::displayMainMenu(); // Prompt again for valid input
  }

  switch (choice)
  {
  case 1:
  {
    std::cout << "Continuing as Guest..." << std::endl;
    return Dashboard::displayGuestMenu();
  }

  case 2:
  {
    clearing();
    std::cout << "Logging in as Member..." << std::endl;
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    User user;
    try
    {
      user.checkAuthentication(username, password);
    }
    catch (const std::invalid_argument &e)
    {
      std::cout << "Error: " << e.what() << std::endl;
      // waiting for 3 seconds
      waiting(3);
      return Dashboard::displayMainMenu();
    }

    Member member;
    try
    {
      member.findMemberByUser(user);
    }
    catch (const std::invalid_argument &e)
    {
      std::cout << "Error: " << e.what() << std::endl;
      // waiting for 3 seconds
      waiting(3);
      return Dashboard::displayMainMenu();
    }
    std::cout << "Welcome back, " << member.getFullname() << "!" << std::endl;
    this->member = &member;
    this->currentRole = "Member";
    return Dashboard::displayMemberMenu();
  }

  case 3:
  {
    clearing();
    std::cout << "Logging in as Admin..." << std::endl;

    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    User user;
    try
    {
      user.checkAuthentication(username, password);
    }
    catch (const std::invalid_argument &e)
    {
      std::cout << "Error: " << e.what() << std::endl;
      // waiting for 3 seconds
      waiting(3);
      return Dashboard::displayMainMenu();
    }

    Admin admin;
    try
    {
      admin.getAdminByUser(user);
    }
    catch (const std::invalid_argument &e)
    {
      std::cout << "Error: " << e.what() << std::endl;
      // waiting for 3 seconds
      waiting(3);
      return Dashboard::displayMainMenu();
    }

    std::cout << "Welcome back " << user.getUsername() << "!" << std::endl;
    this->admin = &admin;
    this->currentRole = "Admin";

    return Dashboard::displayAdminMenu();
  }

  case 4:
  {
    clearing();
    User user;
    try
    {
      std::cout << "Signing up as Member..." << std::endl;
      // Create a new user
      std::string username, password;
      std::cout << "Enter username: ";
      std::cin >> username;
      std::cout << "Enter password: ";
      std::cin >> password;
      user = User(username, password);
      user.save();
    }
    catch (const std::invalid_argument &e)
    {
      std::cout << "Error: " << e.what() << std::endl;
      // waiting for 3 seconds
      waiting(3);
      return Dashboard::displayMainMenu();
    }
    try
    {
      // Create a new member
      std::string fullname, phoneNumber, email;
      // Get whole line including spaces
      std::cout << "Enter full name: ";
      getline(std::cin >> std::ws, fullname);
      std::cout << "Enter phone number: ";
      std::cin >> phoneNumber;
      std::cout << "Enter email: ";
      std::cin >> email;

      std::cout << "Press 1 if you want to use passport number, press 2 if you want to use citizen ID number: ";
      int choice;
      std::cin >> choice;
      if (choice != 1 && choice != 2)
      {
        std::cout << "Invalid choice. Please try again." << std::endl;
        // waiting for 3 seconds
        waiting(3);
        return Dashboard::displayMainMenu(); // Prompt again for valid input
      }
      if (choice == 1)
      {
        std::string passportNumber;
        std::cout << "Enter passport number: ";
        std::cin >> passportNumber;
        Member member = Member(fullname, phoneNumber, email, user, "P-" + passportNumber);
        member.save();
      }
      else
      {
        std::string citizenID;
        std::cout << "Enter citizen ID: ";
        std::cin >> citizenID;
        Member member = Member(fullname, phoneNumber, email, user, "C-" + citizenID);
        member.save();
      }
      std::cout << "Member account created successfully!" << std::endl;
      waiting(3);
    }
    catch (const std::invalid_argument &e)
    {
      std::cout << "Error: " << e.what() << std::endl;
      // waiting for 3 seconds
      waiting(3);
      return Dashboard::displayMainMenu();
    }
    return Dashboard::displayMainMenu();
  }

  case 5:
  {
    clearing();
    std::cout << "Signing up as Admin..." << std::endl;
    User user;
    try
    {
      // Create a new user
      std::string username, password;
      std::cout << "Enter username: ";
      std::cin >> username;
      std::cout << "Enter password: ";
      std::cin >> password;
      user = User(username, password);
      user.save();
    }
    catch (const std::invalid_argument &e)
    {
      std::cout << "Error: " << e.what() << std::endl;
      // waiting for 3 seconds
      waiting(3);
      return Dashboard::displayMainMenu();
    }
    try
    {
      Admin admin = Admin(user);
      admin.save();
    }
    catch (const std::invalid_argument &e)
    {
      std::cout << "Error: " << e.what() << std::endl;
      // waiting for 3 seconds
      waiting(3);
      return Dashboard::displayMainMenu();
    }
    std::cout << "Admin account created successfully!" << std::endl;
    // waiting for 3 seconds
    waiting(3);
    return Dashboard::displayMainMenu();
  }

  case 6:
  {
    std::cout << "Exiting the application." << std::endl;
    exit(0);
  }

  default:
  {
    std::cout << "Invalid choice. Please try again." << std::endl;
    // waiting for 3 seconds
    waiting(3);
    return Dashboard::displayMainMenu(); // Prompt again for valid input
  }
  }
}