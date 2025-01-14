#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <iostream>

#include "./User.h"
#include "./Member.h"
#include "./Admin.h"

class Dashboard
{
private:
  std::string currentRole;
  User *user;
  Member *member;
  Admin *admin;

public:
  // Constructor
  Dashboard();

  // Method to display the main menu options
  void displayMainMenu();

  // Method to handle the main menu options
  void handleMainMenu(bool clear);
};

#endif