#include "../libs/Bid.h"

// Default constructor
Bid::Bid() : automaticBid(false), limitPrice(0.0f) {}

// Parameterized constructor
Bid::Bid(std::string bidID, Member member, Item item, bool automaticBid, float limitPrice)
    : bidID(bidID), member(member), item(item), automaticBid(automaticBid), limitPrice(limitPrice) {}

// Getters
std::string Bid::getBidID() {
    return bidID;
}

Member Bid::getMember() {
    return member;
}

Item Bid::getItem() {
    return item;
}

bool Bid::isAutomaticBid() {
    return automaticBid;
}

float Bid::getLimitPrice() {
    return limitPrice;
}

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