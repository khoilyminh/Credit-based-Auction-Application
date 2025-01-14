#ifndef REVIEW_H
#define REVIEW_H

#include <string>

class Review
{
private:
    std::string reviewID;
    std::string memberID;
    std::string reviewerID;
    std::string content;
    int rating; // Rating out of 5

public:
    // Constructors
    Review();
    Review(std::string reviewID, std::string memberID, std::string reviewerID, std::string content, int rating);

    // Getters
    std::string getReviewID();
    std::string getMemberID();
    std::string getReviewerID();
    std::string getContent();
    int getRating();

    // Setters
    void setContent(std::string content);
    void setRating(int rating);

    // Other methods
    std::string toString();
};

#endif