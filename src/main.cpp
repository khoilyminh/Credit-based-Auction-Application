#include <iostream>

#include "./libs/Dashboard.h"
#include "./libs/Auction.h"

int main()
{
  // // Testing the Dashboard
  // Dashboard dashboard;
  // dashboard.displayMainMenu();

  Auction auction("Auction A");
  auction.save();

  return 0;
}