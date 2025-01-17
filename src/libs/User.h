#include <string>

#ifndef USER_H
#define USER_H

class User
{
private:
  std::string userID;
  std::string username;
  std::string password;
  bool status;

public:
  // ------- Constructors -------
  /** This constructor create an empty user instance. */
  User();
  /** This constructor create a user instance with the given parameters. Only use this constructor for loading the database. */
  User(std::string userID, std::string username, std::string password, bool status);
  /** This constructor create a user instance with the given parameters. */
  User(std::string username, std::string password);

  // ------- Getters -------
  std::string getUserID();
  std::string getUsername();
  std::string getPassword();
  bool checkPassword(std::string password);
  bool getStatus();

  // ------- Setters -------
  void setUsername(std::string username);
  void setPassword(std::string password);
  void setStatus(bool status);

  // ------- Other methods -------
  std::string toString();
  void save();
  /** This function is used to check username and password */
  void checkAuthentication(std::string username, std::string password);
};

#endif
