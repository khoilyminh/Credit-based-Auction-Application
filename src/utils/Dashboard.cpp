#include "../libs/Dashboard.h"

Dashboard::Dashboard()
{
  // Constructor
}

void Dashboard::displayWelcomeScreen()
{
  std::cout << "====================================" << std::endl;
  std::cout << "   Welcome to the Credit-Based     " << std::endl;
  std::cout << "         Auction Application        " << std::endl;
  std::cout << "====================================" << std::endl;
}

void Dashboard::displayMainMenu()
{
  std::cout << "Please choose an option:" << std::endl;
  std::cout << "1. Continue as Guest" << std::endl;
  std::cout << "2. Login as Member" << std::endl;
  std::cout << "3. Login as Admin" << std::endl;
  std::cout << "4. Exit" << std::endl;
}

void Dashboard::handleMainMenu()
{
  int choice;
  std::cin >> choice;

  switch (choice)
  {
  case 1:
    std::cout << "Continuing as Guest..." << std::endl;
    // Add logic for guest functionality
    break;
  case 2:
    std::cout << "Logging in as Member..." << std::endl;
    // Add logic for member login
    break;
  case 3:
    std::cout << "Logging in as Admin..." << std::endl;
    // Add logic for admin login
    break;
  case 4:
    std::cout << "Exiting the application." << std::endl;
    exit(0);
  default:
    std::cout << "Invalid choice. Please try again." << std::endl;
    handleUserInput(); // Prompt again for valid input
    break;
  }
}