#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <vector>

class Item {
 private:
  std::string itemID;
  std::string itemName;
  std::string category;
  std::string description;
  float startingBidAmount;
  float currentBidAmount;
  float bidIncrement;
  float minBuyerRating;
  std::string auctionID;

 public:
  // Constructors
  Item();
  Item(std::string itemID, std::string itemName, std::string category,
       std::string description, float startingBidAmount, float currentBidAmount,
       float bidIncrement, float minBuyerRating, std::string auctionID);
  Item(std::string itemName, std::string category, std::string description,
       float startingBidAmount, float bidIncrement, float minBuyerRating,
       std::string auctionID);

  // Getters
  std::string getItemID();
  std::string getItemName();
  std::string getCategory();
  std::string getDescription();
  float getStartingBidAmount();
  float getCurrentBidAmount();
  float getBidIncrement();
  float getMinBuyerRating();
  std::string getAuctionID();

  // Setters
  void setItemName(std::string itemName);
  void setCategory(std::string category);
  void setDescription(std::string description);
  void setStartingBidAmount(float startingBidAmount);
  void setCurrentBidAmount(float currentBidAmount);
  void setBidIncrement(float bidIncrement);
  void setMinBuyerRating(float minBuyerRating);
  void setAuctionID(std::string auctionID);

  // Other methods

  // This function will allow users to place a bid on an item
  std::string toString();

  void save();  // Method to save the item to the database
};

#endif
