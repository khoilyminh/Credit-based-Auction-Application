#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <iostream>

#include "./Admin.h"
#include "./Auction.h"
#include "./Item.h"
#include "./Member.h"
#include "./Transaction.h"
#include "./User.h"

class Dashboard {
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

  // ------- Admin methods -------

  void displayAdminMenu();

  void handleAdminMenu(bool clear);

  // ------- Auction methods for admin -------

  void displayAdminAuctionMenu();

  void handleAdminAuctionMenu(bool clear);

  void displayAdminAuctionDetailMenu(Auction *auction);

  void handleAdminAuctionDetailMenu(Auction *auction, bool clear);

  // ------- Member methods -------

  void displayMemberMenu();

  void handleMemberMenu(bool clear);

  // ------- Auction methods for member -------

  void displayMemberAuctionMenu();

  void handleMemberAuctionMenu(bool clear);

  void displayMemberAuctionDetailMenu(Auction *auction);

  void handleMemberAuctionDetailMenu(Auction *auction, bool clear);

  // ------- Items methods -------

  void displayItemsMenu(Auction *auction);

  void handleItemsMenu(Auction *auction, bool clear);

  void displayItemsDetailMenu(Item *item, Auction *auction);

  void handleItemsDetailMenu(Item *item, Auction *auction, bool clear);

  // ------- Guest methods -------

  void displayGuestMenu();

  // ------- Transaction methods -------

  void displayTransactionDetailedMenu(Transaction *transaction);

  void handleTransactionDetailedMenu(Transaction *transaction, bool clear);
};

#endif