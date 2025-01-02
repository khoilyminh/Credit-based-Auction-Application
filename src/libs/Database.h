#ifndef DATABASE_H
#define DATABASE_H

#include <vector>

#include "./User.h"

class Database {
 private:
  std::vector<User> users;
  /** This function is used to save the whole user list to file. */
  void saveUsersToFile();

 public:
  Database();

  // ------- User methods -------

  /** This function get all user in the database. */
  std::vector<User> getAllUsers();
  /** This function is used to get user by userID. */
  User* getUserByID(std::string userID);
  /** This function is used to add or update user in the database. */
  void saveUser(User* user);
  /** This function is used to remove a user from the database. */
  void removeUser(User user);
};

#endif