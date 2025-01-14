#ifndef BID_H
#define BID_H

#include <string>
#include "Member.h"
#include "Item.h"

class Bid {
private:
    std::string bidID;
    Member member;
    Item item;
    bool automaticBid;
    float limitPrice;

public:
    // Constructors
    Bid();
    Bid(std::string bidID, Member member, Item item, bool automaticBid, float limitPrice);

    // Getters
    std::string getBidID();
    Member getMember();
    Item getItem();
    bool isAutomaticBid();
    float getLimitPrice();

    // Methods
    void placeBid(Member member, float bidAmount);
    void updateDetails();
    void removeListing();
    void closeAuction();
};

#endif