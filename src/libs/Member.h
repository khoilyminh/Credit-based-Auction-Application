#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include <vector>

#include "User.h"

class Member
{
private:
  std::string memberID;
  std::string fullname;
  std::string phoneNumber;
  std::string email;
  float rating;
  int credit;
  std::string userID;
  std::string IDNumber;

public:
  // ------- Constructors -------

  /** This constructor create a blank member instance. */
  Member();
  /** This constructor create a member instance with provide parameters. Only
   * use this constructor for loading from database. */
  Member(std::string memberID, std::string fullname, std::string phoneNumber,
         std::string email, float rating, int credit, std::string userID, std::string IDNumber);
  /** This constructor create a member instance with provide parameters. Use
   * this for create new member. */
  Member(std::string fullname, std::string phoneNumber, std::string email,
         User user, std::string IDNumber);

  // ------- Getters -------

  /** Get member ID. */
  std::string getMemberID();
  /** Get member full name. */
  std::string getFullname();
  /** Get member phone number. */
  std::string getPhoneNumber();
  /** Get member email. */
  std::string getEmail();
  /** Get member rating. */
  float getRating();
  /** Get member reviews. */
  std::vector<std::string> getReviews();
  /** Get member credit. */
  int getCredit();
  /** Get user ID. */
  std::string getUserID();
  /** Get ID number. */
  std::string getIDNumber();

  // ------- Setters -------
  /** This function is used to set the fullname of member instance. */
  void setFullname(std::string fullname);
  /** This function is used to set the phone number of member instance. */
  void setPhoneNumber(std::string phoneNumber);
  /** This function is used to set the email of member instance. */
  void setEmail(std::string email);
  /** This function is used to set the rating of member instance. */
  void setRating(float rating);
  /** This function is used to set the credit of member instance. */
  void setCredit(int credit);
  /** This function is used to set the user ID of member instance. */
  void setUserID(std::string userID);
  /** This function is used to set the ID number of member instance. */
  void setIDNumber(std::string IDNumber);

  // ------- Other methods -------
  /** This method will print out the information of member instance. */
  void print();
  /** This method will convert the member instance to string. */
  std::string toString();
  /** This method will get the user instance of the member instance. */
  User *getUser();
  /** This method will save the member instance to the database. */
  void save();
  /** This method will find the member instance by user instance. */
  void *findMemberByUser(User user);
};

#endif
