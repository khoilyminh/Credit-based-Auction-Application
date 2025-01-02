#include "../libs/Database.h"

#include <fstream>
#include <vector>

#include "../libs/User.h"

// ------- User methods -------

void Database::saveUsersToFile() {
  std::ofstream file("./data/users.txt", std::ios::trunc);
  for (int i = 0; i < this->users.size(); i++) {
    file << this->users[i].getUserID() << " " << this->users[i].getUsername()
         << " " << this->users[i].getPassword() << std::endl;
  }
  file.close();
}

std::vector<User> getAllUsersFromDatabase() {
  std::vector<User> users;
  std::ifstream file("./data/users.txt", std::ios::in);
  std::string line;
  while (std::getline(file, line)) {
    // The first value is the userID, the second value is the username, and the
    // third value is the password.
    std::string userID = line.substr(0, line.find(" "));
    line = line.substr(line.find(" ") + 1);
    std::string username = line.substr(0, line.find(" "));
    line = line.substr(line.find(" ") + 1);
    std::string password = line;
    // Create a new user object and add it to the users vector.
    User user(userID, username, password);
    users.push_back(user);
  }
  file.close();
  return users;
}

Database::Database() { this->users = getAllUsersFromDatabase(); }

std::vector<User> Database::getAllUsers() { return this->users; }

User* Database::getUserByID(std::string userID) {
  for (int i = 0; i < this->users.size(); i++) {
    if (this->users[i].getUserID() == userID) {
      return &this->users[i];
    }
  }
  return NULL;
}

void Database::saveUser(User* user) {
  for (int i = 0; i < this->users.size(); i++) {
    if (this->users[i].getUserID() == user->getUserID()) {
      this->users[i] = *user;
      return;
    }
  }
  this->users.push_back(*user);
  // Update the data in the file.
  this->saveUsersToFile();
}

void Database::removeUser(User user) {
  for (int i = 0; i < this->users.size(); i++) {
    if (this->users[i].getUserID() == user.getUserID()) {
      this->users.erase(this->users.begin() + i);
      break;
    }
  }
  // Update the data in the file.
  this->saveUsersToFile();
}