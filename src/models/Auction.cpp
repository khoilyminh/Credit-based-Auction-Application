#include "../libs/Auction.h"
#include "../libs/Database.h"
#include "../libs/IDGenerator.h"

#include <iostream>
#include <stdexcept>
#include <ctime>

// Define constants
#define DEFAULT_AUCTION_ID_LENGTH 16
#define DEFAULT_AUCTION_NAME ""
#define DEFAULT_START_TIME 0
#define DEFAULT_END_TIME 0

// ------- Constructors -------

// Default constructor
Auction::Auction()
{
  this->auctionID = IDGenerator::generateID(16);
  this->auctionName = DEFAULT_AUCTION_NAME;
  this->startTime = DEFAULT_START_TIME;
  this->endTime = DEFAULT_END_TIME;
}

Auction::Auction(std::string auctionID, std::string auctionName, std::time_t startTime, std::time_t endTime)
    : auctionID(auctionID), auctionName(auctionName)
{
  this->startTime = startTime;
  this->endTime = endTime;
}

// Parameterized constructor
Auction::Auction(std::string auctionName)
    : auctionName(auctionName)
{
  this->auctionID = IDGenerator::generateID(DEFAULT_AUCTION_ID_LENGTH);
  this->startTime = DEFAULT_START_TIME;
  this->endTime = DEFAULT_END_TIME;
}

// ------- Getters -------

std::string Auction::getAuctionID()
{
  return auctionID;
}

std::string Auction::getAuctionName()
{
  return auctionName;
}

std::time_t Auction::getStartTime()
{
  return startTime;
}

std::time_t Auction::getEndTime()
{
  return endTime;
}

std::vector<Item> Auction::getItems()
{
  return items;
}

// ------- Setters -------

void Auction::setAuctionName(std::string auctionName)
{
  this->auctionName = auctionName;
}

// ------- Other methods -------

void Auction::addItem(Item item)
{
  items.push_back(item);
}

void Auction::removeItem(std::string itemID)
{
  for (int index = 0; index < items.size(); index++)
  {
    if (items[index].getItemID() == itemID)
    {
      items.erase(items.begin() + index);
      break;
    }
  }
}

void Auction::startAuction()
{
  if (this->startTime != 0)
  {
    throw std::invalid_argument("Auction has already started.");
  }
  std::time_t startTime;
  time(&startTime);
  this->startTime = startTime;
}

void Auction::endAuction()
{
  if (this->endTime != 0)
  {
    throw std::invalid_argument("Auction has already ended.");
  }
  std::time_t endTime;
  time(&endTime);
  this->endTime = endTime;
}

std::string Auction::toString()
{
  std::string startTime;
  if (this->startTime == 0)
  {
    startTime = "Not started";
  }
  else
  {
    startTime = ctime(&this->startTime);
    // Remove endline of the string
    startTime.pop_back();
  }

  std::string endTime;
  if (this->endTime == 0)
  {
    endTime = "Not ended";
  }
  else
  {
    endTime = ctime(&this->endTime);
    // Remove endline of the string
    endTime.pop_back();
  }

  return "Auction ID: " + this->auctionID + ", Name: " + this->auctionName + ", Start Time: " + startTime + ", End Time: " + endTime;
}

void Auction::save()
{
  Database database;
  database.saveAuction(this);
}
