#include <string>
#include <stdlib.h>

#include "../libs/Dashboard.h"
#include "../libs/User.h"
#include "../libs/Member.h"

Dashboard::Dashboard()
{
  // Constructor
}

void Dashboard::displayMainMenu()
{
  std::system("clear");
  std::cout << "====================================" << std::endl;
  std::cout << "   Welcome to the Credit-Based     " << std::endl;
  std::cout << "         Auction Application        " << std::endl;
  std::cout << "====================================" << std::endl;
  std::cout << std::endl;
  std::cout << "Please choose an option:" << std::endl;
  std::cout << "1. Continue as Guest" << std::endl;
  std::cout << "2. Login as Member" << std::endl;
  std::cout << "3. Login as Admin" << std::endl;
  std::cout << "4. Sign up as Member" << std::endl;
  std::cout << "5. Sign up as Admin" << std::endl;
  std::cout << "6. Exit" << std::endl;
  return Dashboard::handleMainMenu();
}

void Dashboard::handleMainMenu()
{
  std::system("clear");

  int choice;
  std::cout << "Enter your choice: ";
  std::cin >> choice;

  switch (choice)
  {
  case 1:
  {
    std::cout << "Continuing as Guest..." << std::endl;
    // Add logic for guest functionality
    break;
  }

  case 2:
  {
    std::cout << "Logging in as Member..." << std::endl;
    break;
  }

  case 3:
  {
    std::cout << "Logging in as Admin..." << std::endl;
    // Add logic for admin login
    break;
  }

  case 4:
  {
    std::cout << "Signing up as Member..." << std::endl;
    // Create a new user
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;
    User user = User(username, password);
    user.save();
    // Create a new member
    std::string fullname, phoneNumber, email;
    std::cout << "Enter full name: ";
    std::cin >> fullname;
    std::cout << "Enter phone number: ";
    std::cin >> phoneNumber;
    std::cout << "Enter email: ";
    std::cin >> email;
    Member member = Member(fullname, phoneNumber, email, user);
    member.save();
    return Dashboard::handleMainMenu();
  }

  case 5:
  {
    std::cout << "Signing up as Admin..." << std::endl;
    // Add logic for admin sign up
    break;
  }

  case 6:
  {
    std::cout << "Exiting the application." << std::endl;
    exit(0);
  }

  default:
  {
    std::cout << "Invalid choice. Please try again." << std::endl;
    Dashboard::handleMainMenu(); // Prompt again for valid input
    break;
  }
  }
}