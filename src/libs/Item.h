#ifndef ITEM_H
#define ITEM_H

#include <vector>
#include <string>

class Item
{
private:
  std::string itemID;
  std::string itemName;
  std::string category;
  std::string description;
  float startingBid;
  float currentBid;
  std::string highestBidderID;
  float bidIncrement;
  float minBuyerRating;

public:
  // Constructors
  Item();
  Item(std::string itemID, std::string itemName, std::string category, std::string description, float startingBid, float currentBid, std::string highestBidderID, float bidIncrement, float minBuyerRating);
  Item(std::string itemName, std::string category, std::string description, float startingBid, float bidIncrement, float minBuyerRating);

  // Getters
  std::string getItemID();
  std::string getItemName();
  std::string getCategory();
  std::string getDescription();
  float getStartingBid();
  float getCurrentBid();
  std::string getHighestBidderID();

  // Setters
  void setItemName(std::string itemName);
  void setCategory(std::string category);
  void setDescription(std::string description);
  void setStartingBid(float startingBid);
  void setCurrentBid(float currentBid);
  void setHighestBidderID(std::string bidderID);

  // Other methods

  // This function will allow users to place a bid on an item
  void placeBid(float bidAmount, std::string bidderID);
  std::string toString();

  void save(); // Method to save the item to the database
};

#endif