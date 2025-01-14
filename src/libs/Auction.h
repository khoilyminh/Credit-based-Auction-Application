#ifndef AUCTION_H
#define AUCTION_H

#include <vector>
#include "Item.h"

class Auction
{
private:
    std::vector<Item> items;
    std::string auctionID;
    std::string auctionName;
    std::string startTime;
    std::string endTime;

public:
    // Constructors
    Auction();
    Auction(std::string auctionID, std::string auctionName, std::string startTime, std::string endTime);

    // Getters
    std::string getAuctionID();
    std::string getAuctionName();
    std::string getStartTime();
    std::string getEndTime();
    std::vector<Item> getItems();

    // Setters
    void setAuctionName(std::string auctionName);
    void setStartTime(std::string startTime);
    void setEndTime(std::string endTime);

    // Other methods
    void addItem(Item item);
    void removeItem(std::string itemID);
    void startAuction();
    void endAuction();
    std::string toString();
};

#endif