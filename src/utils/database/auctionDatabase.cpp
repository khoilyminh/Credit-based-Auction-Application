#include <unistd.h>

#include <fstream>
#include <iostream>
#include <vector>

#include "../../libs/Database.h"
#include "../../libs/Item.h"
#include "../../libs/Member.h"
#include "../../libs/User.h"

void Database::saveAuctionsToFile() {
  std::ofstream file("./data/auctions.txt", std::ios::trunc);
  for (Auction &auction : this->auctions) {
    file << auction.getAuctionID() << ", " << auction.getAuctionName() << ", "
         << auction.getStartTime() << ", " << auction.getEndTime() << std::endl;
  }
  file.close();
}

std::vector<Auction> Database::getAllAuctions() { return this->auctions; }

Auction *Database::getAuctionByID(std::string auctionID) {
  for (int index = 0; index < this->auctions.size(); index++) {
    if (this->auctions.at(index).getAuctionID() == auctionID) {
      return &this->auctions.at(index);
    }
  }
  return nullptr;
}

void Database::saveAuction(Auction *auction) {
  bool isExist = false;
  for (int index = 0; index < this->auctions.size(); index++) {
    // If the auction is exist in the database, update the auction.
    if (this->auctions.at(index).getAuctionID() == auction->getAuctionID()) {
      this->auctions.at(index) = *auction;
      isExist = true;
      break;
    }
  }
  // If the auction is not exist in the database, add it to the database.
  if (!isExist) this->auctions.push_back(*auction);
  // Update the data in the file.
  this->saveAuctionsToFile();
}

void Database::removeAuction(Auction auction) {
  for (int index = 0; index < this->auctions.size(); index++) {
    if (this->auctions.at(index).getAuctionID() == auction.getAuctionID()) {
      this->auctions.erase(this->auctions.begin() + index);
      break;
    }
  }
  // Update the data in the file.
  this->saveAuctionsToFile();
}
