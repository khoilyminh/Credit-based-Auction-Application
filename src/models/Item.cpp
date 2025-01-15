#include "../libs/Item.h"

#include <iostream>
#include <regex>
#include <stdexcept>

#include "../libs/Database.h"
#include "../libs/IDGenerator.h"

// Define constants
#define ITEM_ID_LENGTH 16
#define DEFAULT_ITEMNAME ""
#define DEFAULT_CATEGORY ""
#define DEFAULT_DESCRIPTION ""
#define DEFAULT_STARTING_BID_AMOUNT 0.0f
#define DEFAULT_CURRENT_BID_AMOUNT 0.0f
#define DEFAULT_BID_INCREMENT 0.0f
#define DEFAULT_MIN_BUYER_RATING 0.0f

// ------- Constructors -------

// Default constructor
Item::Item() {
  this->itemID = IDGenerator::generateID(ITEM_ID_LENGTH);
  this->itemName = DEFAULT_ITEMNAME;
  this->category = DEFAULT_CATEGORY;
  this->description = DEFAULT_DESCRIPTION;
  this->startingBidAmount = DEFAULT_STARTING_BID_AMOUNT;
  this->currentBidAmount = DEFAULT_CURRENT_BID_AMOUNT;
  this->bidIncrement = DEFAULT_BID_INCREMENT;
  this->minBuyerRating = DEFAULT_MIN_BUYER_RATING;
}

// Parameterized constructor
Item::Item(std::string itemID, std::string itemName, std::string category,
           std::string description, float startingBidAmount,
           float currentBidAmount, float bidIncrement, float minBuyerRating) {
  this->itemID = itemID;
  this->itemName = itemName;
  this->category = category;
  this->description = description;
  this->startingBidAmount = startingBidAmount;
  this->currentBidAmount = currentBidAmount;
  this->bidIncrement = bidIncrement;
  this->minBuyerRating = minBuyerRating;
}

Item::Item(std::string itemName, std::string category, std::string description,
           float startingBidAmount, float bidIncrement, float minBuyerRating) {
  this->itemID = IDGenerator::generateID(ITEM_ID_LENGTH);
  this->itemName = itemName;
  this->category = category;
  this->description = description;
  this->startingBidAmount = startingBidAmount;
  this->currentBidAmount = DEFAULT_CURRENT_BID_AMOUNT;
  this->bidIncrement = bidIncrement;
  this->minBuyerRating = minBuyerRating;
}

// ------- Getters -------

std::string Item::getItemID() { return this->itemID; }

std::string Item::getItemName() { return this->itemName; }

std::string Item::getCategory() { return this->category; }

std::string Item::getDescription() { return this->description; }

float Item::getStartingBidAmount() { return this->startingBidAmount; }

float Item::getCurrentBidAmount() { return this->currentBidAmount; }

float Item::getBidIncrement() { return this->bidIncrement; }

float Item::getMinBuyerRating() { return this->minBuyerRating; }

// ------- Setters -------

void Item::setItemName(std::string itemName) { this->itemName = itemName; }

void Item::setCategory(std::string category) { this->category = category; }

void Item::setDescription(std::string description) {
  this->description = description;
}

void Item::setStartingBidAmount(float startingBidAmount) {
  this->startingBidAmount = startingBidAmount;
}

void Item::setCurrentBidAmount(float currentBidAmount) {
  this->currentBidAmount = currentBidAmount;
}

void Item::setBidIncrement(float bidIncrement) {
  this->bidIncrement = bidIncrement;
}

void Item::setMinBuyerRating(float minBuyerRating) {
  this->minBuyerRating = minBuyerRating;
}

// ------- Other methods -------

std::string Item::toString() {
  return "Item ID: " + itemID + ", Name: " + itemName +
         ", Category: " + category + ", Description: " + description +
         ", Starting Bid Amount: " + std::to_string(startingBidAmount) +
         ", Current Bid Amount: " + std::to_string(currentBidAmount) +
         ", Bid Increment: " + std::to_string(bidIncrement) +
         ", Min Buyer Rating: " + std::to_string(minBuyerRating);
}

void Item::save() { Database().saveItem(this); }
