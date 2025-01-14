#include <string>
#include <stdlib.h>
// #include <windows.h> // For Windows OS
#include <unistd.h> // For Unix-based OS
#include <ctime>

#include "../libs/Dashboard.h"
#include "../libs/User.h"
#include "../libs/Member.h"
#include "../libs/Admin.h"
#include "../libs/Auction.h"
#include "../libs/Database.h"

#define NULL_TIME -2209075200

Dashboard::Dashboard()
{
}

void Dashboard::displayMainMenu()
{
  std::system("clear");
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
    return Dashboard::displayMemberMenu();
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
    return Dashboard::displayMainMenu(); // Prompt again for valid input
  }
  }
}

// ------- Admin Menu -------

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
    return Dashboard::displayAdminAuctionMenu();
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

// ------- Auction Menu for admin -------

void Dashboard::displayAdminAuctionMenu()
{
  std::system("clear");
  std::cout << "====================================" << std::endl;
  std::cout << "  Auctions Menu for Administrator   " << std::endl;
  std::cout << "====================================" << std::endl;
  std::cout << std::endl;

  std::cout << "0. Back to admin menu." << std::endl;

  Database database;
  int index = 1;
  for (Auction &auction : database.getAllAuctions())
  {
    std::cout << index << ". " << auction.getAuctionName() << std::endl;
    index++;
  }

  return Dashboard::handleAdminAuctionMenu(false);
}

void Dashboard::handleAdminAuctionMenu(bool clear = true)
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
    // Check if choice is integer and within the range of auctions
    Database database;
    if (choice < 0 || choice > database.getAllAuctions().size())
    {
      std::cout << "Invalid choice. Please try again." << std::endl;
      // Wait for 3 seconds
      sleep(3);
      return Dashboard::displayAdminAuctionMenu();
    }
    else
    {
      Auction auction = database.getAllAuctions().at(choice - 1);
      return Dashboard::displayAdminAuctionDetailMenu(&auction);
    }
  }
  }
  return Dashboard::displayAdminAuctionMenu();
}

void Dashboard::displayAdminAuctionDetailMenu(Auction *auction)
{
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
  std::cout << "Start time: " << (auction->getStartTime() == -1 ? "Not yet" : startTime) << std::endl;
  std::cout << "End time: " << (auction->getEndTime() == -1 ? "Not yet" : endTime) << std::endl;
  std::cout << std::endl;

  std::cout << "Please choose an option:" << std::endl;
  std::cout << "0. Back to admin auction menu." << std::endl;
  std::cout << "1. Start auction." << std::endl;
  std::cout << "2. End auction." << std::endl;

  return Dashboard::handleAdminAuctionDetailMenu(auction, false);
}

void Dashboard::handleAdminAuctionDetailMenu(Auction *auction, bool clear = true)
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
    return Dashboard::displayAdminAuctionMenu();
  }

  case 1:
  {
    try
    {
      auction->startAuction();
      auction->save();
    }
    catch (const std::invalid_argument &e)
    {
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

  case 2:
  {
    try
    {
      auction->endAuction();
      auction->save();
    }
    catch (const std::invalid_argument &e)
    {
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

  default:
  {
    std::cout << "Invalid choice. Please try again." << std::endl;
    // Wait for 3 seconds
    sleep(3);
    break;
  }
  }
  return Dashboard::displayAdminAuctionDetailMenu(auction);
}

// ------- Member Menu -------

void Dashboard::displayMemberMenu()
{
  std::system("clear");
  std::cout << "====================================" << std::endl;
  std::cout << "            Member Menu             " << std::endl;
  std::cout << "====================================" << std::endl;
  std::cout << std::endl;
  std::cout << "Please choose an option:" << std::endl;
  std::cout << "0. Logout" << std::endl;
  std::cout << "1. View my account" << std::endl;
  std::cout << "2. View active auction" << std::endl;
  return Dashboard::handleMemberMenu(false);
}

void Dashboard::handleMemberMenu(bool clear = true)
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
    std::cout << "Logging out..." << std::endl;
    this->member = nullptr;
    this->currentRole = "";
    return Dashboard::displayMainMenu();
  }

  case 1:
  {
    std::system("clear");
    std::cout << "====================================" << std::endl;
    std::cout << "          Account detailed          " << std::endl;
    std::cout << "====================================" << std::endl
              << std::endl;
    std::cout << "Member ID: " << this->member->getMemberID() << std::endl;
    std::cout << "Full name: " << this->member->getFullname() << std::endl;
    std::cout << "Phone number: " << this->member->getPhoneNumber() << std::endl;
    std::cout << "Email: " << this->member->getEmail() << std::endl;
    std::cout << "Credit: " << this->member->getCredit() << std::endl;
    std::cout << "Rating score: " << this->member->getRating() << std::endl;
    std::cout << std::endl
              << "Return to member menu in 10 seconds..." << std::endl;
    // Wait 10 seconds
    sleep(10);
    return Dashboard::displayMemberMenu();
  }

  case 2:
  {
    break;
  }

  default:
  {
    std::cout << "Invalid choice. Please try again." << std::endl;
    // Wait for 3 seconds
    sleep(3);
    break;
  }
  }
  return Dashboard::displayMemberMenu();
}
