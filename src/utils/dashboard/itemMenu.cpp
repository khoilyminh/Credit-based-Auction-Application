#include <stdlib.h>
#include <string>
#include <ctime>

#include "../../libs/Auction.h"
#include "../../libs/Dashboard.h"
#include "../../libs/Database.h"
#include "../../libs/Member.h"
#include "../../libs/Review.h"
#include "../..//libs/waiting.h"
#include "../../libs/clearing.h"

Item *processAutomaticBid(Bid currentBid, Bid lastBid, Item *item)
{
  // Check if lastBid is automatic
  if (!lastBid.isAutomaticBid())
  {
    item->setCurrentBidAmount(currentBid.getBidAmount());
    item->save();
    return item;
  }

  // Check if lastBid reach the limit price
  if (lastBid.getBidAmount() + item->getBidIncrement() >
      lastBid.getLimitPrice())
  {
    item->setCurrentBidAmount(currentBid.getBidAmount());
    item->save();
    return item;
  }

  lastBid.setBidAmount(lastBid.getBidAmount() + item->getBidIncrement());
  lastBid.save();
  item->setCurrentBidAmount(lastBid.getBidAmount());
  item->save();

  return processAutomaticBid(lastBid, currentBid, item);
}

void Dashboard::displayItemsMenu(Auction *auction)
{
  clearing();
  std::cout << "=====================================" << std::endl;
  std::cout << "       Buying items in auction       " << std::endl;
  std::cout << "=====================================" << std::endl;
  std::cout << std::endl;

  std::cout << "0. Back to member auction detail menu." << std::endl;

  std::vector<Item> filteredItems;
  Database database;
  for (Item &item : database.getAllItems())
  {
    if (item.getAuctionID() == auction->getAuctionID() &&
        item.getMinBuyerRating() <= this->member->getRating())
    {
      filteredItems.push_back(item);
    }
  }

  int index = 1;
  for (Item &item : filteredItems)
  {
    std::cout << index << ". " << item.getItemName() << std::endl;
    index++;
  }
  return Dashboard::handleItemsMenu(auction, false);
}

void Dashboard::handleItemsMenu(Auction *auction, bool clear = true)
{
  if (clear)
    clearing();
  std::cout << "Enter your choice: ";
  int choice;
  std::cin >> choice;

  // Check if choice is integer
  if (std::cin.fail())
  {
    std::cin.clear();
    std::cin.ignore();
    std::cout << "Invalid choice. Please try again." << std::endl;
    // waiting for 3 seconds
    waiting(3);
    return Dashboard::displayItemsMenu(auction);
  }

  switch (choice)
  {
  case 0:
  {
    return Dashboard::displayMemberAuctionDetailMenu(auction);
  }

  default:
  {
    // Check if choice is integer and within the range of items
    std::vector<Item> filteredItems;
    Database database;
    for (Item &item : database.getAllItems())
    {
      if (item.getAuctionID() == auction->getAuctionID() &&
          item.getMinBuyerRating() <= this->member->getRating())
      {
        filteredItems.push_back(item);
      }
    }

    if (choice < 0 || choice > filteredItems.size())
    {
      std::cout << "Invalid choice. Please try again." << std::endl;
      // waiting for 3 seconds
      waiting(3);
      return Dashboard::displayItemsMenu(auction);
    }
    else
    {
      Item item = filteredItems.at(choice - 1);
      return Dashboard::displayItemsDetailMenu(&item, auction);
    }
  }
  }
  return Dashboard::displayItemsMenu(auction);
}

void Dashboard::displayItemsDetailMenu(Item *item, Auction *auction)
{
  clearing();
  std::cout << "=====================================" << std::endl;
  std::cout << "     Item Detail Menu for Member     " << std::endl;
  std::cout << "=====================================" << std::endl;
  std::cout << std::endl;

  Database database;
  Member seller = *database.getMemberByID(item->getSellerID());

  std::cout << "Item ID: " << item->getItemID() << std::endl;
  std::cout << "Item name: " << item->getItemName() << std::endl;
  std::cout << "Item description: " << item->getDescription() << std::endl;
  std::cout << "Item category: " << item->getCategory() << std::endl;
  std::cout << "Seller name: " << seller.getFullname() << std::endl;
  std::cout << "Starting bid amount: " << item->getStartingBidAmount()
            << std::endl;
  std::cout << "Bid increment: " << item->getBidIncrement() << std::endl;
  std::cout << "Current bid amount: " << item->getCurrentBidAmount()
            << std::endl;
  std::cout << std::endl;

  std::cout << "Please choose an option:" << std::endl;
  std::cout << "0. Back to items menu." << std::endl;
  std::cout << "1. Place bid." << std::endl;
  std::cout << "2. Remove item." << std::endl;
  std::cout << "3. View seller information." << std::endl;
  std::cout << "4. View seller reviews." << std::endl;
  return Dashboard::handleItemsDetailMenu(item, auction, false);
}

void Dashboard::handleItemsDetailMenu(Item *item, Auction *auction,
                                      bool clear = true)
{
  if (clear)
    clearing();
  std::cout << "Enter your choice: ";
  int choice;
  std::cin >> choice;

  // Check if choice is integer
  if (std::cin.fail())
  {
    std::cin.clear();
    std::cin.ignore();
    std::cout << "Invalid choice. Please try again." << std::endl;
    // waiting for 3 seconds
    waiting(3);
    return Dashboard::displayItemsDetailMenu(item, auction);
  }

  switch (choice)
  {
  case 0:
  {
    return Dashboard::displayItemsMenu(auction);
  }

  case 1:
  {
    clearing();
    std::cout << "=====================================" << std::endl;
    std::cout << "       Placing bid for item          " << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << std::endl;

    // Check if member is the seller of item
    if (this->member->getMemberID() == item->getSellerID())
    {
      std::cout << "You cannot place bid on your own item." << std::endl;
      // waiting for 3 seconds
      waiting(3);
      return Dashboard::displayItemsDetailMenu(item, auction);
    }

    // Check if auction is started
    if (auction->getStartTime() == 0)
    {
      std::cout << "Auction has not started yet." << std::endl;
      // waiting for 3 seconds
      waiting(3);
      return Dashboard::displayItemsDetailMenu(item, auction);
    }

    // Check if auction is ended
    if (auction->getEndTime() != 0)
    {
      std::cout << "Auction has ended." << std::endl;
      // waiting for 3 seconds
      waiting(3);
      return Dashboard::displayItemsDetailMenu(item, auction);
    }

    // Check if member already placed a bid Database database;
    Database database;
    for (Bid &bid : database.getAllBids())
    {
      if (bid.getMemberID() == this->member->getMemberID() &&
          bid.getItemID() == item->getItemID())
      {
        std::cout << "You have already placed a bid on this item."
                  << std::endl;
        // waiting for 3 seconds
        waiting(3);
        return Dashboard::displayItemsDetailMenu(item, auction);
      }
    }

    float bidAmount;
    std::cout << "Enter bid amount: ";
    std::cin >> bidAmount;

    // Check if bid amount is greater than current bid amount
    if (bidAmount <= item->getCurrentBidAmount())
    {
      std::cout << "Bid amount must be greater than current bid amount."
                << std::endl;
      // waiting for 3 seconds
      waiting(3);
      return Dashboard::displayItemsDetailMenu(item, auction);
    }

    // Check if bid amount is greater than member credit
    if (bidAmount > this->member->getCredit())
    {
      std::cout << "Bid amount must be less than or equal to your credit."
                << std::endl;
      // waiting for 3 seconds
      waiting(3);
      return Dashboard::displayItemsDetailMenu(item, auction);
    }

    if (item->getCurrentBidAmount() != 0 &&
        bidAmount - item->getCurrentBidAmount() < item->getBidIncrement())
    {
      std::cout << "Bid amount must be at least $"
                << item->getCurrentBidAmount() + item->getBidIncrement()
                << "." << std::endl;
      // waiting for 3 seconds
      waiting(3);
      return Dashboard::displayItemsDetailMenu(item, auction);
    }
    else if (item->getCurrentBidAmount() == 0 &&
             bidAmount <
                 item->getStartingBidAmount() + item->getBidIncrement())
    {
      std::cout << "Bid amount must be at least $"
                << item->getStartingBidAmount() + item->getBidIncrement()
                << "." << std::endl;
      // waiting for 3 seconds
      waiting(3);
      return Dashboard::displayItemsDetailMenu(item, auction);
    }

    std::cout
        << "Do you want to place an automatic bid? (Y for yes, N for no): ";
    char choice;
    std::cin >> choice;
    bool automaticBid = choice == 'Y' || choice == 'y';

    float limitPrice = 0;
    if (automaticBid)
    {
      std::cout << "Enter limit price: ";
      std::cin >> limitPrice;

      // Check if limit price is greater than bid amount
      if (limitPrice <= bidAmount)
      {
        std::cout << "Limit price must be greater than bid amount."
                  << std::endl;
        // waiting for 3 seconds
        waiting(3);
        return Dashboard::displayItemsDetailMenu(item, auction);
      }

      // Check if limit price is greater than member credit
      if (limitPrice > this->member->getCredit())
      {
        std::cout << "Limit price must be less than or equal to your credit."
                  << std::endl;
        // waiting for 3 seconds
        waiting(3);
        return Dashboard::displayItemsDetailMenu(item, auction);
      }

      // Check if the limit price is unique
      for (Bid &bid : database.getAllBids())
      {
        std::cout << "Bid limit price: " << bid.getLimitPrice() << std::endl;
        if (bid.getLimitPrice() == limitPrice &&
            bid.getItemID() == item->getItemID())
        {
          // waiting for 3 seconds
          waiting(3);
          return Dashboard::displayItemsDetailMenu(item, auction);
        }
      }
    }

    if (item->getCurrentBidAmount() != 0 &&
        bidAmount - item->getCurrentBidAmount() < item->getBidIncrement())
    {
      std::cout << "Bid amount must be greater than current bid amount by at "
                   "least the bid increment."
                << std::endl;
      // waiting for 3 seconds
      waiting(3);
      return Dashboard::displayItemsDetailMenu(item, auction);
    }

    // In case of first bid
    if (item->getCurrentBidAmount() == 0)
    {
      Bid bid(*this->member, *item, bidAmount, automaticBid, limitPrice);
      bid.save();
      item->setCurrentBidAmount(bidAmount);
      item->save();
      std::cout << "Bid placed successfully! You are leading the aunction!"
                << std::endl;
    }
    else
    {
      std::cout << "Checking for fighting bids..." << std::endl;

      // Get the last bid
      Bid lastBid;
      for (Bid &tempBid : database.getAllBids())
      {
        if (tempBid.getItemID() == item->getItemID() &&
            tempBid.getBidAmount() == item->getCurrentBidAmount())
        {
          lastBid = tempBid;
          break;
        }
      }
      std::cout << "Found last bid: " << lastBid.getBidAmount() << std::endl;

      Bid currentBid(*this->member, *item, bidAmount, automaticBid,
                     limitPrice);
      currentBid.save();
      item->setCurrentBidAmount(bidAmount);
      item->save();

      item = processAutomaticBid(currentBid, lastBid, item);
    }

    // waiting for 3 seconds
    waiting(3);
    // Reload the item
    return Dashboard::displayItemsDetailMenu(item, auction);
  }

  case 2:
  {
    // Check if member is the seller of item
    if (this->member->getMemberID() != item->getSellerID())
    {
      std::cout << "You cannot remove an item that you do not own."
                << std::endl;
      // waiting for 3 seconds
      waiting(3);
      return Dashboard::displayItemsDetailMenu(item, auction);
    }

    if (item->getCurrentBidAmount() == 0)
    {
      Database database;
      database.removeItem(*item);

      std::cout << "Item removed successfully!" << std::endl;
      // waiting for 3 seconds
      waiting(3);
      return Dashboard::displayItemsMenu(auction);
    }
    else
    {
      std::cout << "You cannot remove an item that has bids on it."
                << std::endl;
      // waiting for 3 seconds
      waiting(3);
      return Dashboard::displayItemsDetailMenu(item, auction);
    }
  }

  case 3:
  {
    clearing();
    std::cout << "=====================================" << std::endl;
    std::cout << "         Seller information          " << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << std::endl;

    Database database;
    Member seller = *database.getMemberByID(item->getSellerID());
    std::cout << "Seller name: " << seller.getFullname() << std::endl;
    std::cout << "Seller email: " << seller.getEmail() << std::endl;
    std::cout << "Seller phone number: " << seller.getPhoneNumber()
              << std::endl;
    std::cout << "Seller rating: " << seller.getRating() << std::endl;
    std::cout << std::endl;

    std::cout << "Please choose an option:" << std::endl;
    std::cout << "0. Back to item detail menu." << std::endl;

    int choice;
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    // Check if choice is integer
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore();
      std::cout << "Invalid choice. Please try again." << std::endl;
      // waiting for 3 seconds
      waiting(3);
      return Dashboard::displayItemsDetailMenu(item, auction);
    }
    if (choice == 0)
    {
      return Dashboard::displayItemsDetailMenu(item, auction);
    }
    else
    {
      std::cout << "Invalid choice. Please try again." << std::endl;
      // waiting for 3 seconds
      waiting(3);
      return Dashboard::displayItemsDetailMenu(item, auction);
    }
  }

  case 4:
  {
    clearing();
    std::cout << "=====================================" << std::endl;
    std::cout << "            Seller reviews           " << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << std::endl;

    Database database;
    std::vector<Review> filterReviews;
    for (Review &review : database.getAllReviews())
    {
      if (review.getMemberID() == item->getSellerID())
      {
        std::cout << "From: " << database.getMemberByID(review.getReviewerID())->getFullname() << std::endl;
        std::cout << "Rating: " << review.getRating() << std::endl;
        std::cout << "Comment: " << review.getContent() << std::endl;
        std::cout << std::endl;
      }
    }

    std::cout << "0. Back to item detail menu." << std::endl;
    std::cout << "Enter your choice: ";
    int choice;
    std::cin >> choice;

    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore();
      std::cout << "Invalid choice. Please try again." << std::endl;
      // waiting for 3 seconds
      waiting(3);
      return Dashboard::displayItemsDetailMenu(item, auction);
    }
    else if (choice == 0)
    {
      return Dashboard::displayItemsDetailMenu(item, auction);
    }
    else
    {
      std::cout << "Invalid choice. Please try again." << std::endl;
      // waiting for 3 seconds
      waiting(3);
      return Dashboard::displayItemsDetailMenu(item, auction);
    }
  }

  default:
  {
    std::cout << "Invalid choice. Please try again." << std::endl;
    // waiting for 3 seconds
    waiting(3);
    break;
  }
  }
  return Dashboard::displayItemsDetailMenu(item, auction);
}
