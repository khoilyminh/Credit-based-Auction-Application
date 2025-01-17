#include "../libs/Admin.h"
#include "../libs/IDGenerator.h"
#include "../libs/Database.h"

#include <stdexcept>
#include <vector>
#include <iostream>

#define ADMIN_ID_LENGTH 16

Admin::Admin()
{
  this->adminID = "";
  this->userID = "";
};

Admin::Admin(std::string adminID, std::string userID)
{
  this->adminID = adminID;
  this->userID = userID;
}

Admin::Admin(User user)
{
  this->adminID = IDGenerator::generateID(ADMIN_ID_LENGTH);
  this->userID = user.getUserID();
}

std::string Admin::getAdminID()
{
  return this->adminID;
}

std::string Admin::getUserID()
{
  return this->userID;
}

void Admin::setUserID(std::string userID)
{
  Database database = Database();
  // Check if userID is existed
  if (database.getUserByID(userID) == nullptr)
  {
    throw std::invalid_argument("User ID is not existed.");
  }
  else
  {
    this->userID = userID;
  }
}

std::string Admin::toString()
{
  return "Admin ID: " + this->adminID + "\nUser ID: " + this->userID + "\n";
}

void Admin::save()
{
  Database database = Database();
  database.saveAdmin(this);
}

void Admin::getAdminByUser(User user)
{
  Database database = Database();
  std::vector<Admin> admins = database.getAllAdmins();
  for (Admin &admin : admins)
  {
    if (admin.getUserID() == user.getUserID())
    {
      *this = admin;
      return;
    }
  }
  throw std::invalid_argument("Admin is not existed.");
}
