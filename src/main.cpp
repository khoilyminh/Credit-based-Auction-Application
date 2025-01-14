#include <iostream>

#include "./libs/Database.h"
#include "./libs/User.h"
#include "./libs/Dashboard.h"

int main()
{
  User user = User("peterdinh", "12345678");
  user.save();

  Member member = Member("Peter Dinh", "0867847403", "contact@cuongdinh.dev", user);
  member.save();


  // // Testing the Dashboard
  //   Dashboard dashboard;
  // dashboard.displayWelcomeScreen();
  // dashboard.displayMainMenu();
  // dashboard.handleUserInput();

  return 0;
}