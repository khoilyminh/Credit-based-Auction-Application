#include <vector>
#include <iostream>

#include "../libs/User.h"
#include "../libs/Database.h"
#include "../libs/IDGenerator.h"

#define DEFAULT_USERNAME ""
#define DEFAULT_PASSWORD ""
#define DEFAULT_STATUS true

// ------- Default constructor -------

User::User()
{
  this->userID = IDGenerator::generateID(16);
  this->username = DEFAULT_USERNAME;
  this->password = DEFAULT_PASSWORD;
  this->status = DEFAULT_STATUS;
}

// ------- Constructor with parameters -------

User::User(std::string userID, std::string username, std::string password, bool status)
{
  this->userID = userID;
  this->username = username;
  this->password = password;
  this->status = status;
}

User::User(std::string username, std::string password)
{
  this->userID = IDGenerator::generateID(16);
  this->status = DEFAULT_STATUS;
  this->setUsername(username);
  this->setPassword(password);
}

// ------- Getters -------

std::string User::getUserID() { return this->userID; }

std::string User::getUsername() { return this->username; }

std::string User::getPassword() { return this->password; }

bool User::checkPassword(std::string password)
{
  return this->password == password;
}

bool User::getStatus() { return this->status; }

// ------- Setters -------

void User::setUsername(std::string username)
{
  // Check if the username is not empty
  if (username.empty())
  {
    throw std::invalid_argument("The username cannot be empty.");
  }
  // Username only contain alphanumeric characters
  for (int index = 0; index < username.length(); index++)
  {
    if (!isalnum(username[index]))
    {
      throw std::invalid_argument(
          "The username can only contain alphanumeric characters.");
    }
  }
  // Check if the username is unique
  std::vector<User> users = Database().getAllUsers();
  for (User user : users)
  {
    if (user.getUsername() == username)
    {
      throw std::invalid_argument("The username is already taken.");
    }
  }
  // Set the username
  this->username = username;
}

void User::setPassword(std::string password)
{
  // Check if the password is not empty
  if (password.empty())
  {
    throw std::invalid_argument("The password cannot be empty.");
  }
  // Password must be at least 8 characters long
  if (password.length() < 8)
  {
    throw std::invalid_argument(
        "The password must be at least 8 characters long.");
  }
  // Password only allow alphanumeric characters
  for (int index = 0; index < password.length(); index++)
  {
    if (!isalnum(password[index]))
    {
      throw std::invalid_argument(
          "The password can only contain alphanumeric characters.");
    }
  }
  this->password = password;
}

void User::setStatus(bool status) { this->status = status; }

// ------- Other methods -------

std::string User::toString()
{
  std::string hiddenPassword = "********";
  std::string status = this->status ? "active" : "inactive";
  return "UserID: " + this->getUserID() + ", Username: " + this->getUsername() +
         ", Password: " + hiddenPassword + ", Status: " + status + "\n";
}

void User::save()
{
  if (this->username != DEFAULT_USERNAME)
  {
    Database().saveUser(this);
  }
}

void User::checkAuthentication(std::string username, std::string password)
{
  std::vector<User> users = Database().getAllUsers();
  for (User &user : users)
  {
    if (user.getUsername() == username && user.checkPassword(password))
    {
      *this = user;
      return;
    }
  }
  throw std::invalid_argument("Invalid username or password.");
}
