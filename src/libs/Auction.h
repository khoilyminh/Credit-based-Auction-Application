#ifndef AUCTION_H
#define AUCTION_H

#include <vector>
#include <ctime>

#include "Item.h"

class Auction
{
private:
  std::vector<Item> items;
  std::string auctionID;
  std::string auctionName;
  std::time_t startTime;
  std::time_t endTime;

public:
  // Constructors
  Auction();
  Auction(std::string auctionID, std::string auctionName, std::time_t startTime, std::time_t endTime);
  Auction(std::string auctionName);

  // Getters
  std::string getAuctionID();
  std::string getAuctionName();
  std::time_t getStartTime();
  std::time_t getEndTime();
  std::vector<Item> getItems();

  // Setters
  void setAuctionName(std::string auctionName);

  // Other methods
  void addItem(Item item);
  void removeItem(std::string itemID);
  void startAuction();
  void endAuction();
  std::string toString();
  void save();
};

#endif