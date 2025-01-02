#include "../libs/User.h"

#include <iostream>

#include "../libs/IDGenerator.h"

// ------- Default constructor -------

User::User() {
  this->userID = IDGenerator::generateID(16);
  this->username = "";
  this->password = "";
}

// ------- Constructor with parameters -------

User::User(std::string userID, std::string username, std::string password) {
  this->userID = userID;
  this->setUsername(username);
  this->setPassword(password);
}

User::User(std::string username, std::string password) {
  this->userID = IDGenerator::generateID(16);
  this->setUsername(username);
  this->setPassword(password);
}

// ------- Getters -------

std::string User::getUserID() { return this->userID; }

std::string User::getUsername() { return this->username; }

std::string User::getPassword() { return this->password; }

bool User::checkPassword(std::string password) {
  return this->password == password;
}

// ------- Setters -------

void User::setUsername(std::string username) {
  // Check if the username is not empty
  if (username.empty()) {
    throw std::invalid_argument("The username cannot be empty.");
  }
  // Username only contain alphanumeric characters
  for (int index = 0; index < username.length(); index++) {
    if (!isalnum(username[index])) {
      throw std::invalid_argument(
          "The username can only contain alphanumeric characters.");
    }
  }
  this->username = username;
}

void User::setPassword(std::string password) {
  // Check if the password is not empty
  if (password.empty()) {
    throw std::invalid_argument("The password cannot be empty.");
  }
  // Password must be at least 8 characters long
  if (password.length() < 8) {
    throw std::invalid_argument(
        "The password must be at least 8 characters long.");
  }
  // Password only allow alphanumeric characters
  for (int index = 0; index < password.length(); index++) {
    if (!isalnum(password[index])) {
      throw std::invalid_argument(
          "The password can only contain alphanumeric characters.");
    }
  }
  this->password = password;
}

// ------- Other methods -------

std::string User::toString() {
  std::string hiddenPassword = "********";
  return "UserID: " + this->getUserID() + ", Username: " + this->getUsername() +
         ", Password: " + hiddenPassword + "\n";
}
