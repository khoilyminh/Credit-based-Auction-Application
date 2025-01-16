#include <unistd.h>

#include <fstream>
#include <iostream>
#include <vector>

#include "../../libs/Database.h"
#include "../../libs/User.h"

void Database::saveAdminsToFile()
{
  std::ofstream file("./data/admins.txt", std::ios::trunc);
  for (int i = 0; i < this->admins.size(); i++)
  {
    file << this->admins[i].getAdminID() << ", " << this->admins[i].getUserID()
         << std::endl;
  }
  file.close();
}

std::vector<Admin> Database::getAllAdmins() { return this->admins; }

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