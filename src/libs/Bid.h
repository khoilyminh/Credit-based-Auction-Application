#ifndef BID_H
#define BID_H

#include <string>

#include "Item.h"
#include "Member.h"

class Bid {
 private:
  std::string bidID;
  std::string memberID;
  std::string itemID;
  float bidAmount;
  bool automaticBid;
  float limitPrice;

 public:
  // Constructors
  Bid();
  Bid(std::string bidID, std::string memberID, std::string itemID,
      float bidAmount, bool automaticBid, float limitPrice);
  Bid(Member member, Item item, float bidAmount, bool automaticBid,
      float limitPrice);

  // Getters
  std::string getBidID();
  std::string getMemberID();
  std::string getItemID();
  float getBidAmount();
  bool isAutomaticBid();
  float getLimitPrice();

  // Methods
  void placeBid(Member member, float bidAmount);
  void updateDetails();
  void removeListing();
  void closeAuction();
};

#endif