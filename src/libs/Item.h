#ifndef ITEM_H
#define ITEM_H

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

public:
    // Constructors
    Item();
    Item(std::string itemID, std::string itemName, std::string category, std::string description, float startingBid);

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
    void placeBid(float bidAmount, std::string bidderID);
    std::string toString();
};

#endif