#include <unistd.h>

#include <fstream>
#include <iostream>
#include <vector>

#include "../../libs/Database.h"
#include "../../libs/User.h"

void Database::saveUsersToFile()
{
  std::ofstream file("./data/users.txt", std::ios::trunc);
  for (int i = 0; i < this->users.size(); i++)
  {
    bool status = this->users[i].getStatus() ? "active" : "inactive";
    file << this->users[i].getUserID() << ", " << this->users[i].getUsername()
         << ", " << this->users[i].getPassword() << ", " << status << std::endl;
  }
  file.close();
}

std::vector<User> Database::getAllUsers() { return this->users; }

User *Database::getUserByID(std::string userID)
{
  for (int index = 0; index < this->users.size(); index++)
  {
    if (this->users.at(index).getUserID() == userID)
    {
      return &this->users.at(index);
    }
  }
  return nullptr;
}

void Database::saveUser(User *user)
{
  bool isExist = false;
  for (int index = 0; index < this->users.size(); index++)
  {
    // If the user is exist in the database, update the user.
    if (this->users.at(index).getUserID() == user->getUserID())
    {
      this->users.at(index) = *user;
      isExist = true;
      break;
    }
  }
  // If the user is not exist in the database, add it to the database.
  if (!isExist)
    this->users.push_back(*user);
  // Update the data in the file.
  this->saveUsersToFile();
}

void Database::removeUser(User user)
{
  for (int index = 0; index < this->users.size(); index++)
  {
    if (this->users.at(index).getUserID() == user.getUserID())
    {
      this->users.erase(this->users.begin() + index);
      break;
    }
  }
  // Update the data in the file.
  this->saveUsersToFile();
  // Remove all member that have the same userID.
  for (int index = 0; index < this->members.size(); index++)
  {
    if (this->members.at(index).getUserID() == user.getUserID())
    {
      this->members.erase(this->members.begin() + index);
      index--;
    }
  }
}