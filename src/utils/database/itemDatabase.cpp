#include <unistd.h>

#include <fstream>
#include <iostream>
#include <vector>

#include "../../libs/Database.h"
#include "../../libs/Item.h"

std::vector<Item> Database::getAllItems() { return this->items; }

void Database::saveItemsToFile()
{
  std::ofstream file("./data/items.txt", std::ios::trunc);
  for (int i = 0; i < this->items.size(); i++)
  {
    file << this->items[i].getItemID() << ", " << this->items[i].getItemName()
         << ", " << this->items[i].getCategory() << ", "
         << this->items[i].getDescription() << ", "
         << this->items[i].getSellerID() << ", "
         << this->items[i].getStartingBidAmount() << ", "
         << this->items[i].getCurrentBidAmount() << ", "
         << this->items[i].getBidIncrement() << ", "
         << this->items[i].getMinBuyerRating() << ", "
         << this->items[i].getAuctionID() << std::endl;
  }
  file.close();
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
