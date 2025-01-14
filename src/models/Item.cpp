#include "../libs/Item.h"
#include "../libs/IDGenerator.h"
#include "../libs/Database.h"

#include <iostream>
#include <stdexcept>
#include <regex>

// Define constants
#define ITEM_ID_LENGTH 16
#define DEFAULT_ITEMNAME ""
#define DEFAULT_CATEGORY ""
#define DEFAULT_DESCRIPTION ""
#define DEFAULT_STARTING_BID 0.0f
#define DEFAULT_CURRENT_BID 0.0f

// ------- Constructors -------

// Default constructor
Item::Item() : startingBid(DEFAULT_STARTING_BID), currentBid(DEFAULT_CURRENT_BID)
{
  this->itemID = IDGenerator::generateID(ITEM_ID_LENGTH);
  this->itemName = DEFAULT_ITEMNAME;
  this->category = DEFAULT_CATEGORY;
  this->description = DEFAULT_DESCRIPTION;
  this->highestBidderID = "";
}

// Parameterized constructor
Item::Item(std::string itemID, std::string itemName, std::string category, std::string description, float startingBid)
    : itemID(itemID), itemName(itemName), category(category), description(description), startingBid(startingBid), currentBid(startingBid), highestBidderID("") {}

// ------- Getters -------

std::string Item::getItemID()
{
  return itemID;
}

std::string Item::getItemName()
{
  return itemName;
}

std::string Item::getCategory()
{
  return category;
}

std::string Item::getDescription()
{
  return description;
}

float Item::getStartingBid()
{
  return startingBid;
}

float Item::getCurrentBid()
{
  return currentBid;
}

std::string Item::getHighestBidderID()
{
  return highestBidderID;
}

// ------- Setters -------

void Item::setItemName(std::string itemName)
{
  this->itemName = itemName;
}

void Item::setCategory(std::string category)
{
  this->category = category;
}

void Item::setDescription(std::string description)
{
  this->description = description;
}

void Item::setStartingBid(float startingBid)
{
  this->startingBid = startingBid;
}

void Item::setCurrentBid(float currentBid)
{
  this->currentBid = currentBid;
}

void Item::setHighestBidderID(std::string bidderID)
{
  this->highestBidderID = bidderID;
}

// ------- Other methods -------

void Item::placeBid(float bidAmount, std::string bidderID)
{
  if (bidAmount > currentBid)
  {
    currentBid = bidAmount;
    highestBidderID = bidderID;
  }
  else
  {
    throw std::invalid_argument("Bid amount must be higher than the current bid.");
  }
}

std::string Item::toString()
{
  return "Item ID: " + itemID + ", Name: " + itemName + ", Category: " + category +
         ", Description: " + description + ", Starting Bid: " + std::to_string(startingBid) +
         ", Current Bid: " + std::to_string(currentBid) + ", Highest Bidder ID: " + highestBidderID;
}

void Item::save()
{
  Database().saveItem(this);
}