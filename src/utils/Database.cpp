#include <fstream>
#include <vector>
#include <iostream>

#include "../libs/User.h"
#include "../libs/Member.h"
#include "../libs/Item.h"
#include "../libs/Database.h"

std::vector<User> getAllUsersFromDatabase()
{
  std::vector<User> users;
  std::ifstream file("./data/users.txt", std::ios::in);
  std::string line;
  while (std::getline(file, line))
  {
    // The first value is the userID, the second value is the username, and the
    // third value is the password, the forth value will be status.
    std::string userID = line.substr(0, line.find(", "));
    line = line.substr(line.find(", ") + 1);
    std::string username = line.substr(1, line.find(", ") - 1);
    line = line.substr(line.find(", ") + 1);
    std::string password = line.substr(1, line.find(", ") - 1);
    line = line.substr(line.find(", ") + 2);
    bool status = line.substr(line.find(", ") + 1) == "1";
    // Create a new user object and add it to the users vector.
    User user(userID, username, password, status);
    users.push_back(user);
  }
  file.close();
  return users;
}

std::vector<Member> getAllMembersFromDatabase()
{
  std::vector<Member> members;
  std::ifstream file("./data/members.txt", std::ios::in);
  std::string line;
  while (std::getline(file, line))
  {
    // The first value is the memberID, the second value is the fullname, the
    // third value is the phoneNumber, the fourth value is the email, the fifth
    // value is the creditPoint, the sixth value is the rating, the seventh
    // value is the credit, and the eighth value is the userID.
    std::string memberID = line.substr(0, line.find(", "));
    line = line.substr(line.find(" ") + 1);
    std::string fullname = line.substr(0, line.find(", "));
    line = line.substr(line.find(", ") + 1);
    std::string phoneNumber = line.substr(1, line.find(", ") - 1);
    line = line.substr(line.find(", ") + 1);
    std::string email = line.substr(1, line.find(", ") - 1);
    line = line.substr(line.find(", ") + 1);
    int creditPoint = std::stoi(line.substr(1, line.find(", ") - 1));
    line = line.substr(line.find(", ") + 1);
    float rating = std::stof(line.substr(1, line.find(", ") - 1));
    line = line.substr(line.find(", ") + 1);
    int credit = std::stoi(line.substr(1, line.find(", ") - 1));
    line = line.substr(line.find(", ") + 1);
    std::string userID = line.substr(1, line.find(", ") - 1);
    // Create a new member object and add it to the members vector.
    Member member(memberID, fullname, phoneNumber, email, creditPoint, rating, credit, userID);
    members.push_back(member);
  }
  file.close();
  return members;
}

std::vector<Admin> getAllAdminsFromDatabase()
{
  std::vector<Admin> admins;
  std::ifstream file("./data/admins.txt", std::ios::in);
  std::string line;
  while (std::getline(file, line))
  {
    // The first value is the adminID, the second value is the adminID, and the
    // third value is the userID.
    std::string adminID = line.substr(0, line.find(", "));
    line = line.substr(line.find(", ") + 1);
    std::string userID = line.substr(1, line.find(", "));
    // Create a new admin object and add it to the admins vector.
    Admin admin(adminID, userID);
    admins.push_back(admin);
  }
  file.close();
  return admins;
}

Database::Database()
{
  this->users = getAllUsersFromDatabase();
  this->members = getAllMembersFromDatabase();
  this->admins = getAllAdminsFromDatabase();
}

// ------- User methods -------

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

std::vector<User> Database::getAllUsers()
{
  return this->users;
}

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

// ------- Member methods -------

void Database::saveMembersToFile()
{
  std::ofstream file("./data/members.txt", std::ios::trunc);
  for (int i = 0; i < this->members.size(); i++)
  {
    file << this->members[i].getMemberID() << ", " << this->members[i].getFullname()
         << ", " << this->members[i].getPhoneNumber() << ", " << this->members[i].getEmail()
         << ", " << this->members[i].getCreditPoint() << ", " << this->members[i].getRating()
         << ", " << this->members[i].getCredit() << ", " << this->members[i].getUserID() << std::endl;
  }
  file.close();
}

std::vector<Member> Database::getAllMembers()
{
  return this->members;
}

Member *Database::getMemberByID(std::string memberID)
{
  for (int index = 0; index < this->members.size(); index++)
  {
    if (this->members.at(index).getMemberID() == memberID)
    {
      return &this->members.at(index);
    }
  }
  return nullptr;
}

void Database::saveMember(Member *member)
{
  bool isExist = false;
  for (int index = 0; index < this->members.size(); index++)
  {
    // If the member is exist in the database, update the member.
    if (this->members.at(index).getMemberID() == member->getMemberID())
    {
      this->members.at(index) = *member;
      isExist = true;
      break;
    }
  }
  // If the member is not exist in the database, add it to the database.
  if (!isExist)
    this->members.push_back(*member);
  // Update the data in the file.
  this->saveMembersToFile();
}

void Database::removeMember(Member member)
{
  for (int index = 0; index < this->members.size(); index++)
  {
    if (this->members.at(index).getMemberID() == member.getMemberID())
    {
      this->members.erase(this->members.begin() + index);
      break;
    }
  }
  // Update the data in the file.
  this->saveMembersToFile();
}

// ------- Admin methods -------

void Database::saveAdminsToFile()
{
  std::ofstream file("./data/admins.txt", std::ios::trunc);
  for (int i = 0; i < this->admins.size(); i++)
  {
    file << this->admins[i].getAdminID() << ", " << this->admins[i].getUserID() << std::endl;
  }
  file.close();
}

std::vector<Admin> Database::getAllAdmins()
{
  return this->admins;
}

Admin *Database::getAdminByID(std::string adminID)
{
  for (int index = 0; index < this->admins.size(); index++)
  {
    if (this->admins.at(index).getAdminID() == adminID)
    {
      return &this->admins.at(index);
    }
  }
  return nullptr;
}

void Database::saveAdmin(Admin *admin)
{
  bool isExist = false;
  for (int index = 0; index < this->admins.size(); index++)
  {
    // If the admin is exist in the database, update the admin.
    if (this->admins.at(index).getAdminID() == admin->getAdminID())
    {
      this->admins.at(index) = *admin;
      isExist = true;
      break;
    }
  }
  // If the admin is not exist in the database, add it to the database.
  if (!isExist)
    this->admins.push_back(*admin);
  // Update the data in the file.
  this->saveAdminsToFile();
}

void Database::removeAdmin(Admin admin)
{
  for (int index = 0; index < this->admins.size(); index++)
  {
    if (this->admins.at(index).getAdminID() == admin.getAdminID())
    {
      this->admins.erase(this->admins.begin() + index);
      break;
    }
  }
  // Update the data in the file.
  this->saveAdminsToFile();
}

// ------- Item methods -------

void Database::saveItemsToFile()
{
  std::ofstream file("./data/items.txt", std::ios::trunc);
  for (int i = 0; i < this->items.size(); i++)
  {
    file << this->items[i].getItemID() << ", " << this->items[i].getItemName()
         << ", " << this->items[i].getCategory() << ", " << this->items[i].getDescription()
         << ", " << this->items[i].getStartingBid() << ", " << this->items[i].getCurrentBid()
         << ", " << this->items[i].getHighestBidderID() << std::endl;
  }
  file.close();
}

std::vector<Item> Database::getAllItems()
{
  std::vector<Item> items;
  std::ifstream file("./data/items.txt", std::ios::in);
  std::string line;
  while (std::getline(file, line))
  {
    std::string itemID = line.substr(0, line.find(", "));
    line = line.substr(line.find(", ") + 1);
    std::string itemName = line.substr(0, line.find(", "));
    line = line.substr(line.find(", ") + 1);
    std::string category = line.substr(0, line.find(", "));
    line = line.substr(line.find(", ") + 1);
    std::string description = line.substr(0, line.find(", "));
    line = line.substr(line.find(", ") + 1);
    float startingBid = std::stof(line.substr(0, line.find(", ")));
    line = line.substr(line.find(", ") + 1);
    float currentBid = std::stof(line.substr(0, line.find(", ")));
    line = line.substr(line.find(", ") + 1);
    std::string highestBidderID = line;

    // Create a new item object and add it to the items vector.
    Item item(itemID, itemName, category, description, startingBid);
    item.setCurrentBid(currentBid);
    item.setHighestBidderID(highestBidderID);
    items.push_back(item);
  }
  file.close();
  return items;
}

Item *Database::getItemByID(std::string itemID)
{
  for (int index = 0; index < this->items.size(); index++)
  {
    if (this->items.at(index).getItemID() == itemID)
    {
      return &this->items.at(index);
    }
  }
  return NULL;
}

void Database::saveItem(Item *item)
{
  bool isExist = false;
  for (int index = 0; index < this->items.size(); index++)
  {
    // If the item exists in the database, update the item.
    if (this->items.at(index).getItemID() == item->getItemID())
    {
      this->items.at(index) = *item;
      isExist = true;
      break;
    }
  }
  // If the item does not exist in the database, add it to the database.
  if (!isExist)
  {
    this->items.push_back(*item);
  }
  // Update the data in the file.
  this->saveItemsToFile();
}

void Database::removeItem(Item item)
{
  for (int index = 0; index < this->items.size(); index++)
  {
    if (this->items.at(index).getItemID() == item.getItemID())
    {
      this->items.erase(this->items.begin() + index);
      break;
    }
  }
  // Update the data in the file.
  this->saveItemsToFile();
}
