#include "../libs/Database.h"

#include <fstream>
#include <vector>
#include <iostream>

#include "../libs/Member.h"

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
    std::string phoneNumber = line.substr(0, line.find(", "));
    line = line.substr(line.find(", ") + 1);
    std::string email = line.substr(0, line.find(", "));
    line = line.substr(line.find(", ") + 1);
    int creditPoint = std::stoi(line.substr(0, line.find(", ")));
    line = line.substr(line.find(", ") + 1);
    float rating = std::stof(line.substr(0, line.find(", ")));
    line = line.substr(line.find(", ") + 1);
    int credit = std::stoi(line.substr(0, line.find(", ")));
    line = line.substr(line.find(", ") + 1);
    std::string userID = line;
    // Create a new member object and add it to the members vector.
    Member member(memberID, fullname, phoneNumber, email, creditPoint, rating, credit, userID);
    members.push_back(member);
  }
  file.close();
  return members;
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
  return NULL;
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
