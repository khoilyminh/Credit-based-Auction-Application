#include "../libs/Bid.h"

#include "../libs/Database.h"
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
  this->bidAmount = bidAmount;
}

Bid::Bid(std::string bidID, std::string memberID, std::string itemID,
         float bidAmount, bool automaticBid, float limitPrice)
    : bidID(bidID),
      memberID(memberID),
      itemID(itemID),
      automaticBid(automaticBid),
      limitPrice(limitPrice),
      bidAmount(bidAmount) {}

// Getters
std::string Bid::getBidID() { return bidID; }

std::string Bid::getMemberID() { return memberID; }

std::string Bid::getItemID() { return itemID; }

float Bid::getBidAmount() { return bidAmount; }

bool Bid::isAutomaticBid() { return automaticBid; }

float Bid::getLimitPrice() { return limitPrice; }

// Setters

void Bid::setBidID(std::string bidID) { this->bidID = bidID; }

void Bid::setMemberID(std::string memberID) { this->memberID = memberID; }

void Bid::setItemID(std::string itemID) { this->itemID = itemID; }

void Bid::setBidAmount(float bidAmount) { this->bidAmount = bidAmount; }

void Bid::setAutomaticBid(bool automaticBid) {
  this->automaticBid = automaticBid;
}

void Bid::setLimitPrice(float limitPrice) { this->limitPrice = limitPrice; }

// Methods
void Bid::save() {
  Database database;
  database.saveBid(this);
}
