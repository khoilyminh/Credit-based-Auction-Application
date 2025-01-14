#include "../libs/Database.h"
#include <fstream>
#include <vector>
#include <iostream>
#include "../libs/Item.h"

// ------- Item methods -------

void Database::saveItemsToFile()
{
    std::ofstream file("./data/items.txt", std::ios::trunc);
    for (int i = 0; i < this->items.size(); i++)
    {
        file << this->items[i].getItemID() << ", " << this->items[i].getItemName()
             << ", " << this->items[i].getCategory() << ", " << this->items[i].getDescription()
             << ", " << this->items[i].getStartingBid() << ", " << this->items[i].getCurrentBid()
             << ", " << this->items[i].getHighestBidderID() << std::endl;
    }
    file.close();
}

std::vector<Item> Database::getAllItems()
{
    std::vector<Item> items;
    std::ifstream file("./data/items.txt", std::ios::in);
    std::string line;
    while (std::getline(file, line))
    {
        std::string itemID = line.substr(0, line.find(", "));
        line = line.substr(line.find(", ") + 1);
        std::string itemName = line.substr(0, line.find(", "));
        line = line.substr(line.find(", ") + 1);
        std::string category = line.substr(0, line.find(", "));
        line = line.substr(line.find(", ") + 1);
        std::string description = line.substr(0, line.find(", "));
        line = line.substr(line.find(", ") + 1);
        float startingBid = std::stof(line.substr(0, line.find(", ")));
        line = line.substr(line.find(", ") + 1);
        float currentBid = std::stof(line.substr(0, line.find(", ")));
        line = line.substr(line.find(", ") + 1);
        std::string highestBidderID = line;

        // Create a new item object and add it to the items vector.
        Item item(itemID, itemName, category, description, startingBid);
        item.setCurrentBid(currentBid);
        item.setHighestBidderID(highestBidderID);
        items.push_back(item);
    }
    file.close();
    return items;
}

Item *Database::getItemByID(std::string itemID)
{
    for (int index = 0; index < this->items.size(); index++)
    {
        if (this->items.at(index).getItemID() == itemID)
        {
            return &this->items.at(index);
        }
    }
    return NULL;
}

void Database::saveItem(Item *item)
{
    bool isExist = false;
    for (int index = 0; index < this->items.size(); index++)
    {
        // If the item exists in the database, update the item.
        if (this->items.at(index).getItemID() == item->getItemID())
        {
            this->items.at(index) = *item;
            isExist = true;
            break;
        }
    }
    // If the item does not exist in the database, add it to the database.
    if (!isExist)
    {
        this->items.push_back(*item);
    }
    // Update the data in the file.
    this->saveItemsToFile();
}

void Database::removeItem(Item item)
{
    for (int index = 0; index < this->items.size(); index++)
    {
        if (this->items.at(index).getItemID() == item.getItemID())
        {
            this->items.erase(this->items.begin() + index);
            break;
        }
    }
    // Update the data in the file.
    this->saveItemsToFile();
}
