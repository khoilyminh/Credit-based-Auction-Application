#include "../../libs/Review.h"

#include <unistd.h>

#include <fstream>
#include <iostream>
#include <vector>

#include "../../libs/Database.h"
#include "../../libs/Review.h"

void Database::saveReviewsToFile()
{
  std::ofstream file("./data/reviews.txt", std::ios::trunc);
  for (int i = 0; i < this->reviews.size(); i++)
  {
    file << this->reviews[i].getReviewID() << ", "
         << this->reviews[i].getMemberID() << ", "
         << this->reviews[i].getReviewerID() << ", "
         << this->reviews[i].getContent() << ", "
         << this->reviews[i].getRating() << std::endl;
  }
  file.close();
}

std::vector<Review> Database::getAllReviews() { return this->reviews; }

std::vector<Review> Database::getReviewsByMemberID(std::string memberID)
{
  std::vector<Review> reviews;
  for (Review review : this->reviews)
  {
    if (review.getMemberID() == memberID)
    {
      reviews.push_back(review);
    }
  }
  return reviews;
}

void Database::saveReview(Review *review)
{
  bool isExist = false;
  for (int index = 0; index < this->reviews.size(); index++)
  {
    // If the review is exist in the database, update the review.
    if (this->reviews.at(index).getReviewID() == review->getReviewID())
    {
      this->reviews.at(index) = *review;
      isExist = true;
      break;
    }
  }
  // If the review is not exist in the database, add the review.
  if (!isExist)
  {
    this->reviews.push_back(*review);
  }
  this->saveReviewsToFile();
}