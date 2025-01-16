#include <unistd.h>

#include <fstream>
#include <iostream>
#include <vector>

#include "../../libs/Database.h"
#include "../../libs/Item.h"
#include "../../libs/Member.h"
#include "../../libs/User.h"

std::vector<Bid> Database::getAllBids() { return this->bids; }

void Database::saveBidsToFile() {
  std::ofstream file("./data/bids.txt", std::ios::trunc);
  for (Bid &bid : this->bids) {
    file << bid.getBidID() << ", " << bid.getMemberID() << ", "
         << bid.getItemID() << ", " << std::to_string(bid.getBidAmount())
         << ", " << bid.isAutomaticBid() << ", " << bid.getLimitPrice()
         << std::endl;
  }
  file.close();
}

void Database::saveBid(Bid *bid) {
  bool isExist = false;
  for (int index = 0; index < this->bids.size(); index++) {
    // If the bid is exist in the database, update the bid.
    if (this->bids.at(index).getBidID() == bid->getBidID()) {
      this->bids.at(index) = *bid;
      isExist = true;
      break;
    }
  }
  // If the bid is not exist in the database, add it to the database.
  if (!isExist) this->bids.push_back(*bid);
  // Update the data in the file.
  this->saveBidsToFile();
}