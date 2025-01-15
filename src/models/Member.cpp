#include "../libs/Member.h"

#include <iostream>
#include <regex>
#include <cstring>

#include "../libs/Database.h"
#include "../libs/IDGenerator.h"
#include "../libs/User.h"

#define MEMBER_ID_LENGTH 16
#define DEFAULT_FULLNAME ""
#define DEFAULT_PHONE_NUMBER ""
#define DEFAULT_EMAIL ""
#define DEFAULT_RATING 3.0
#define DEFAULT_CREDIT 0

// ------- Constructors -------

Member::Member() {
  this->memberID = IDGenerator::generateID(MEMBER_ID_LENGTH);
  this->fullname = DEFAULT_FULLNAME;
  this->phoneNumber = DEFAULT_PHONE_NUMBER;
  this->email = DEFAULT_EMAIL;
  this->rating = DEFAULT_RATING;
  this->credit = DEFAULT_CREDIT;
}

Member::Member(std::string memberID, std::string fullname,
               std::string phoneNumber, std::string email, float rating,
               int credit, std::string userID) {
  this->memberID = memberID;
  this->fullname = fullname;
  this->phoneNumber = phoneNumber;
  this->email = email;
  this->rating = rating;
  this->credit = credit;
  this->userID = userID;
}

Member::Member(std::string fullname, std::string phoneNumber, std::string email,
               User user) {
  this->memberID = IDGenerator::generateID(MEMBER_ID_LENGTH);
  this->setFullname(fullname);
  this->setPhoneNumber(phoneNumber);
  this->setEmail(email);
  this->rating = DEFAULT_RATING;
  this->credit = DEFAULT_CREDIT;
  this->userID = user.getUserID();
}

// ------- Getters -------

std::string Member::getMemberID() { return this->memberID; }

std::string Member::getFullname() { return this->fullname; }

std::string Member::getPhoneNumber() { return this->phoneNumber; }

std::string Member::getEmail() { return this->email; }

float Member::getRating() { return this->rating; }

int Member::getCredit() { return this->credit; }

// ------- Setters -------

void Member::setFullname(std::string fullname) { this->fullname = fullname; }

void Member::setPhoneNumber(std::string phoneNumber) {
  // Check if phone number is valid
  if (phoneNumber.length() < 10 || phoneNumber.length() > 12) {
    throw std::invalid_argument(
        "Phone number must be between 10 and 12 characters.");
  }
  for (int index = 0; index < phoneNumber.length(); index++) {
    if (phoneNumber[index] < '0' || phoneNumber[index] > '9') {
      throw std::invalid_argument("Phone number must be a number.");
    }
  }
  // Check if phone number is unique
  std::vector<Member> members = Database().getAllMembers();
  for (int index = 0; index < members.size(); index++) {
    if (members[index].getPhoneNumber() == phoneNumber) {
      throw std::invalid_argument("This phone number is already used.");
    }
  }
  // Set phone number
  this->phoneNumber = phoneNumber;
}

void Member::setEmail(std::string email) {
  // Check if email is valid using regex
  // Source: https://regexr.com/3e48o
  // try {
  //   std::regex emailRegex(
  //       "^(([^<>()[\]\.,;:\s@\"]+(\.[^<>()[\]\.,;:\s@\"]+)*)|(\".+\"))@(([^<>()"
  //       "[\]\.,;:\s@\"]+\.)+[^<>()[\]\.,;:\s@\"]{2,})$/i");
  //   if (!std::regex_search(email, emailRegex)) {
  //     throw std::invalid_argument("Email is not valid.");
  //   }
  // } catch (std::regex_error &e) {
  //   std::cerr << "Regex error: " << e.what() << std::endl;
  //   throw std::invalid_argument("Email regex is invalid.");
  // }
  // Check if email is unique
  std::vector<Member> members = Database().getAllMembers();
  for (int index = 0; index < members.size(); index++) {
    if (members[index].getEmail() == email) {
      throw std::invalid_argument("This email address is already used.");
    }
  }
  this->email = email;
}

void Member::setRating(float rating) { this->rating = rating; }

void Member::setCredit(int credit) { this->credit = credit; }

std::string Member::getUserID() {
  // Check if user ID is existed
  return this->userID;
}

// ------- Other methods -------

std::string Member::toString() {
  return "Member ID: " + this->memberID + ", Fullname: " + this->fullname +
         ", Phone number: " + this->phoneNumber + ", Email: " + this->email +
         ", Rating: " + std::to_string(this->rating) +
         ", Credit: " + std::to_string(this->credit) +
         ", User ID: " + this->userID;
}

User *Member::getUser() {
  std::vector<User> users = Database().getAllUsers();
  for (User &user : users) {
    if (user.getUserID() == this->userID) {
      return &user;
    }
    throw std::invalid_argument("User ID does not exist");
  }
  return nullptr;
}

void Member::save() { Database().saveMember(this); }

void *Member::findMemberByUser(User user) {
  Database database;
  std::vector<Member> members = database.getAllMembers();
  bool found = false;
  for (Member &member : members) {
    if (strcmp(member.getUserID().c_str(), user.getUserID().c_str()) == 0) {
      *this = member;
      found = true;
    }
  }
  if (!found) throw std::invalid_argument("Member does not exist.");
  return nullptr;
}
