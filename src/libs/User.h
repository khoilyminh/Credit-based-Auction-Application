#include <string>

#ifndef USER_H
#define USER_H

class User {
 private:
  std::string userID;
  std::string username;
  std::string password;

 public:
  // ------- Constructors -------
  User();
  User(std::string userID, std::string username, std::string password);
  User(std::string username, std::string password);

  // ------- Getters -------
  std::string getUserID();
  std::string getUsername();
  std::string getPassword();
  bool checkPassword(std::string password);

  // ------- Setters -------
  void setUsername(std::string username);
  void setPassword(std::string password);

  // ------- Other methods -------
  std::string toString();
  void save();
};

#endif