#include "../libs/Transaction.h"

#include <ctime>

#include "../libs/Bid.h"
#include "../libs/Database.h"
#include "../libs/IDGenerator.h"
#include "../libs/Item.h"
#include "../libs/Member.h"

#define TRANSACTION_ID_LENGTH 16
#define DEFAULT_BUYER_ID ""
#define DEFAULT_SELLER_ID ""
#define DEFAULT_BID_ID ""
#define DEFAULT_ITEM_ID ""

Transaction::Transaction() {
  this->transactionID = IDGenerator::generateID(TRANSACTION_ID_LENGTH);
  this->buyerID = DEFAULT_BUYER_ID;
  this->sellerID = DEFAULT_SELLER_ID;
  this->bidID = DEFAULT_BID_ID;
  this->itemID = DEFAULT_ITEM_ID;
  std::time_t transactionTime;
  time(&transactionTime);
  this->transactionTime = transactionTime;
}

Transaction::Transaction(std::string transactionID, std::string buyerID,
                         std::string sellerID, std::string bidID,
                         std::string itemID, std::time_t transactionTime) {
  this->transactionID = transactionID;
  this->buyerID = buyerID;
  this->sellerID = sellerID;
  this->bidID = bidID;
  this->itemID = itemID;
  this->transactionTime = transactionTime;
}

Transaction::Transaction(Member buyer, Member seller, Bid bid, Item item) {
  this->transactionID = IDGenerator::generateID(TRANSACTION_ID_LENGTH);
  this->buyerID = buyer.getMemberID();
  this->sellerID = seller.getMemberID();
  this->bidID = bid.getBidID();
  this->itemID = item.getItemID();
  std::time_t transactionTime;
  time(&transactionTime);
  this->transactionTime = transactionTime;
}

std::string Transaction::getTransactionID() { return this->transactionID; }

std::string Transaction::getBuyerID() { return this->buyerID; }

std::string Transaction::getSellerID() { return this->sellerID; }

std::string Transaction::getBidID() { return this->bidID; }

std::string Transaction::getItemID() { return this->itemID; }

std::time_t Transaction::getTransactionTime() { return this->transactionTime; }

void Transaction::setBuyerID(std::string buyerID) { this->buyerID = buyerID; }

void Transaction::setSellerID(std::string sellerID) {
  this->sellerID = sellerID;
}

void Transaction::setBidID(std::string bidID) { this->bidID = bidID; }

void Transaction::setItemID(std::string itemID) { this->itemID = itemID; }

void Transaction::setTransactionTime(std::time_t transactionTime) {
  this->transactionTime = transactionTime;
}

std::string Transaction::toString() {
  return "Transaction ID: " + this->transactionID +
         "\nBuyer ID: " + this->buyerID + "\nSeller ID: " + this->sellerID +
         "\nBid ID: " + this->bidID + "\nItem ID: " + this->itemID +
         "\nTransaction Time: " + std::ctime(&this->transactionTime);
}

void Transaction::save() {
  Database database;
  database.saveTransaction(this);
}