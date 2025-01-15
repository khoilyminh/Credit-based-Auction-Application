#include "../libs/Bid.h"

#include "../libs/IDGenerator.h"

#define BID_ID_LENGTH 16

// Default constructor
Bid::Bid() : automaticBid(false), limitPrice(0.0f) {}

// Parameterized constructor
Bid::Bid(Member member, Item item, float bidAmount, bool automaticBid,
         float limitPrice)
    : automaticBid(automaticBid), limitPrice(limitPrice) {
  this->bidID = IDGenerator::generateID(BID_ID_LENGTH);
  this->memberID = member.getMemberID();
  this->itemID = item.getItemID();
}

Bid::Bid(std::string bidID, std::string memberID, std::string itemID,
         float bidAmount, bool automaticBid, float limitPrice)
    : bidID(bidID),
      memberID(memberID),
      itemID(itemID),
      automaticBid(automaticBid),
      limitPrice(limitPrice) {}

// Getters
std::string Bid::getBidID() { return bidID; }

std::string Bid::getMemberID() { return memberID; }

std::string Bid::getItemID() { return itemID; }

float Bid::getBidAmount() { return bidAmount; }

bool Bid::isAutomaticBid() { return automaticBid; }

float Bid::getLimitPrice() { return limitPrice; }

// Methods
void Bid::placeBid(Member member, float bidAmount) {
  // Logic to place a bid
}

void Bid::updateDetails() {
  // Logic to update bid details
}

void Bid::removeListing() {
  // Logic to remove the bid listing
}

void Bid::closeAuction() {
  // Logic to close the auction
}
