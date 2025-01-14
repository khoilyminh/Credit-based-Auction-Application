#include <string>
#include <stdlib.h>
// #include <windows.h> // For Windows OS
#include <unistd.h> // For Unix-based OS

#include "../libs/Dashboard.h"
#include "../libs/User.h"
#include "../libs/Member.h"
#include "../libs/Admin.h"
#include "../libs/Auction.h"
#include "../libs/Database.h"

Dashboard::Dashboard()
{
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
  return Dashboard::handleMainMenu(false);
}

void Dashboard::handleMainMenu(bool clear = true)
{
  if (clear)
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
    std::system("clear");
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
      // Wait for 3 seconds
      sleep(3);
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
      // Wait for 3 seconds
      sleep(3);
      return Dashboard::displayMainMenu();
    }
    std::cout << "Welcome back, " << member.getFullname() << "!" << std::endl;
    this->member = &member;
    this->currentRole = "Member";
    break;
  }

  case 3:
  {
    std::system("clear");
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
      // Wait for 3 seconds
      sleep(3);
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
      // Wait for 3 seconds
      sleep(3);
      return Dashboard::displayMainMenu();
    }

    std::cout << "Welcome back " << user.getUsername() << "!" << std::endl;
    this->admin = &admin;
    this->currentRole = "Admin";

    return Dashboard::displayAdminMenu();
  }

  case 4:
  {
    std::system("clear");
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
      // Wait for 3 seconds
      sleep(3);
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
      Member member = Member(fullname, phoneNumber, email, user);
      member.save();
    }
    catch (const std::invalid_argument &e)
    {
      std::cout << "Error: " << e.what() << std::endl;
      // Wait for 3 seconds
      sleep(3);
      return Dashboard::displayMainMenu();
    }
    return Dashboard::displayMainMenu();
  }

  case 5:
  {
    std::system("clear");
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
      // Wait for 3 seconds
      sleep(3);
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
      // Wait for 3 seconds
      sleep(3);
      return Dashboard::displayMainMenu();
    }
    std::cout << "Admin account created successfully!" << std::endl;
    // Wait for 3 seconds
    sleep(3);
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
    // Wait for 3 seconds
    sleep(3);
    return Dashboard::handleMainMenu(); // Prompt again for valid input
  }
  }
}

void Dashboard::displayAdminMenu()
{
  std::system("clear");
  std::cout << "====================================" << std::endl;
  std::cout << "         Administrator Menu         " << std::endl;
  std::cout << "====================================" << std::endl;
  std::cout << std::endl;
  std::cout << "Please choose an option:" << std::endl;
  std::cout << "1. Create new auction" << std::endl;
  std::cout << "2. View all auctions" << std::endl;
  std::cout << "5. Logout" << std::endl;
  return Dashboard::handleAdminMenu(false);
}

void Dashboard::handleAdminMenu(bool clear = true)
{
  if (clear)
    std::system("clear");
  std::cout << "Enter your choice: ";
  int choice;
  std::cin >> choice;

  switch (choice)
  {
  case 1:
  {
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

  case 2:
  {
    return Dashboard::displayAuctionMenu();
  }

  case 5:
  {
    std::cout << "Logging out..." << std::endl;
    this->admin = nullptr;
    this->currentRole = "";
    return Dashboard::displayMainMenu();
  }

  default:
  {
    std::cout << "Invalid choice. Please try again." << std::endl;
    // Wait for 3 seconds
    sleep(3);
    break;
  }
  }
  return Dashboard::displayAdminMenu();
}

void Dashboard::displayAuctionMenu()
{
  std::system("clear");
  std::cout << "====================================" << std::endl;
  std::cout << "            Auctions List           " << std::endl;
  std::cout << "====================================" << std::endl;
  std::cout << std::endl;

  std::cout << "0. Back to admin menu." << std::endl;

  Database database;
  int index = 1;
  for (Auction &auction : database.getAllAuctions())
  {
    std::cout << index << ". " << auction.toString() << std::endl;
    index++;
  }

  return Dashboard::handleAuctionMenu(false);
}

void Dashboard::handleAuctionMenu(bool clear = true)
{
  if (clear)
    std::system("clear");
  std::cout << "Enter your choice: ";
  int choice;
  std::cin >> choice;

  switch (choice)
  {
  case 0:
  {
    return Dashboard::displayAdminMenu();
  }

  default:
  {
    std::cout << "Invalid choice. Please try again." << std::endl;
    // Wait for 3 seconds
    sleep(3);
    break;
  }
  }
  return Dashboard::displayAuctionMenu();
}