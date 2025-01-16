#include <unistd.h>

#include <fstream>
#include <iostream>
#include <vector>

#include "../../libs/Database.h"
#include "../../libs/Item.h"
#include "../../libs/Member.h"
#include "../../libs/User.h"

void Database::saveMembersToFile() {
  std::ofstream file("./data/members.txt", std::ios::trunc);
  for (int i = 0; i < this->members.size(); i++) {
    file << this->members[i].getMemberID() << ", "
         << this->members[i].getFullname() << ", "
         << this->members[i].getPhoneNumber() << ", "
         << this->members[i].getEmail() << ", " << this->members[i].getRating()
         << ", " << this->members[i].getCredit() << ", "
         << this->members[i].getUserID() << std::endl;
  }
  file.close();
}

std::vector<Member> Database::getAllMembers() { return this->members; }

Member *Database::getMemberByID(std::string memberID) {
  for (int index = 0; index < this->members.size(); index++) {
    if (this->members.at(index).getMemberID() == memberID) {
      return &this->members.at(index);
    }
  }
  return nullptr;
}

void Database::saveMember(Member *member) {
  bool isExist = false;
  for (int index = 0; index < this->members.size(); index++) {
    // If the member is exist in the database, update the member.
    if (this->members.at(index).getMemberID() == member->getMemberID()) {
      this->members.at(index) = *member;
      isExist = true;
      break;
    }
  }
  // If the member is not exist in the database, add it to the database.
  if (!isExist) this->members.push_back(*member);
  // Update the data in the file.
  this->saveMembersToFile();
}

void Database::removeMember(Member member) {
  for (int index = 0; index < this->members.size(); index++) {
    if (this->members.at(index).getMemberID() == member.getMemberID()) {
      this->members.erase(this->members.begin() + index);
      break;
    }
  }
  // Update the data in the file.
  this->saveMembersToFile();
}