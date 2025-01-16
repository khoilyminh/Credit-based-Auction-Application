#include <vector>
// #include <windows.h> // For Windows OS
#include <unistd.h>  // For Unix-based OS

#include "../../libs/Dashboard.h"
#include "../../libs/Database.h"
#include "../../libs/Item.h"
#include "../../libs/Transaction.h"

void Dashboard::displayGuestMenu() {
  std::system("clear");
  std::cout << "====================================" << std::endl;
  std::cout << "        Items list for Guest        " << std::endl;
  std::cout << "====================================" << std::endl;
  std::cout << std::endl;

  Database database;

  // Get all items
  std::vector<Item> items = database.getAllItems();

  std::vector<Item> filteredItems;
  for (Item &item : database.getAllItems()) {
    if (database.getTransactionsByItemID(item.getItemID()).size() == 0)
      filteredItems.push_back(item);
  }

  int index = 1;

  for (Item &item : filteredItems) {
    std::cout << index << ". " << "Name: " << item.getItemName()
              << ", Description: " << item.getDescription()
              << ", Category: " << item.getCategory() << std::endl;
    index++;
  }

  if (filteredItems.size() == 0) {
    std::cout << "No items available." << std::endl;
  }

  std::cout << std::endl;
  std::cout << "Please select an option: " << std::endl;
  std::cout << "0. Return to main menu." << std::endl;

  int choice;
  std::cout << "Enter your choice: ";
  std::cin >> choice;

  // Check if choice is integer
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore();
    std::cout << "Invalid choice. Please try again." << std::endl;
    // Wait for 3 seconds
    sleep(3);
    return Dashboard::displayGuestMenu();
  }

  if (choice == 0) {
    return Dashboard::displayMainMenu();
  } else {
    std::cout << "Invalid choice. Please try again." << std::endl;
    // Wait for 3 seconds
    sleep(3);
    return Dashboard::displayGuestMenu();
  }
}
