#include "../libs/Review.h"

#include <iostream>
#include <regex>
#include <stdexcept>

#include "../libs/Database.h"
#include "../libs/IDGenerator.h"
#include "../libs/Member.h"

// Define constants
#define DEFAULT_REVIEW_ID ""
#define DEFAULT_CONTENT ""
#define DEFAULT_RATING 1

// ------- Constructors -------

// Default constructor
Review::Review() {
  this->reviewID = IDGenerator::generateID(16);
  this->content = DEFAULT_CONTENT;
  this->rating = DEFAULT_RATING;
}

// Parameterized constructor
Review::Review(std::string reviewID, std::string memberID,
               std::string reviewerID, std::string content, int rating)
    : reviewID(reviewID),
      memberID(memberID),
      reviewerID(reviewerID),
      content(content),
      rating(rating) {}

Review::Review(Member member, Member reviewer, std::string content,
               int rating) {
  this->reviewID = IDGenerator::generateID(16);
  this->memberID = member.getMemberID();
  this->reviewerID = reviewer.getMemberID();
  this->content = content;
  this->rating = rating;
}

// ------- Getters -------

std::string Review::getReviewID() { return reviewID; }

std::string Review::getMemberID() { return memberID; }

std::string Review::getReviewerID() { return reviewerID; }

std::string Review::getContent() { return content; }

int Review::getRating() { return rating; }

// ------- Setters -------

void Review::setContent(std::string content) { this->content = content; }

void Review::setRating(int rating) {
  if (rating < 1 || rating > 5) {
    throw std::invalid_argument("Rating must be between 1 and 5.");
  }
  this->rating = rating;
}

// ------- Other methods -------

std::string Review::toString() {
  return "Review ID: " + reviewID + ", Member ID: " + memberID +
         ", Reviewer ID: " + reviewerID + ", Content: " + content +
         ", Rating: " + std::to_string(rating);
}

void Review::save() {
  Database database;
  database.saveReview(this);
}
