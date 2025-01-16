#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <ctime>

#include "./Bid.h"
#include "./Item.h"
#include "./Member.h"

class Transaction
{
private:
  std::string transactionID;
  std::string buyerID;
  std::string sellerID;
  std::string bidID;
  std::string itemID;
  std::time_t transactionTime;

public:
  // ---------- Constructors ----------

  Transaction();
  Transaction(std::string transactionID, std::string buyerID,
              std::string sellerID, std::string bidID, std::string itemID,
              std::time_t transactionTime);
  Transaction(Member buyer, Member seller, Bid bid, Item item);

  // ---------- Getters ----------

  std::string getTransactionID();
  std::string getBuyerID();
  std::string getSellerID();
  std::string getBidID();
  std::string getItemID();
  std::time_t getTransactionTime();

  // ---------- Setters ----------

  void setBuyerID(std::string buyerID);
  void setSellerID(std::string sellerID);
  void setBidID(std::string bidID);
  void setItemID(std::string itemID);
  void setTransactionTime(std::time_t transactionTime);

  // ------- Other Methods -------
  std::string toString();
  void save();
};

#endif