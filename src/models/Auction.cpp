#include "../libs/Auction.h"
#include "../libs/Database.h"
#include "../libs/IDGenerator.h"

#include <iostream>
#include <stdexcept>

// Define constants
#define DEFAULT_AUCTION_NAME ""
#define DEFAULT_START_TIME ""
#define DEFAULT_END_TIME ""

// ------- Constructors -------

// Default constructor
Auction::Auction()
{
    this->auctionID = IDGenerator::generateID(16);
    this->auctionName = DEFAULT_AUCTION_NAME;
    this->startTime = DEFAULT_START_TIME;
    this->endTime = DEFAULT_END_TIME;
}

// Parameterized constructor
Auction::Auction(std::string auctionID, std::string auctionName, std::string startTime, std::string endTime)
    : auctionID(auctionID), auctionName(auctionName), startTime(startTime), endTime(endTime) {}

// ------- Getters -------

std::string Auction::getAuctionID()
{
    return auctionID;
}

std::string Auction::getAuctionName()
{
    return auctionName;
}

std::string Auction::getStartTime()
{
    return startTime;
}

std::string Auction::getEndTime()
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

void Auction::setStartTime(std::string startTime)
{
    this->startTime = startTime;
}

void Auction::setEndTime(std::string endTime)
{
    this->endTime = endTime;
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
    std::cout << "Auction " << auctionName << " has started!" << std::endl;
}

void Auction::endAuction()
{
    std::cout << "Auction " << auctionName << " has ended!" << std::endl;
}

std::string Auction::toString()
{
    return "Auction ID: " + auctionID + ", Name: " + auctionName + ", Start Time: " + startTime + ", End Time: " + endTime;
}
