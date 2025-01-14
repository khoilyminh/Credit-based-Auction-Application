#include "./User.h"

#ifndef ADMIN_H
#define ADMIN_H

class Admin
{
private:
  std::string adminID;
  std::string userID;

public:
  // ------- Constructors -------
  /** This constructor create an empty admin instance. */
  Admin();
  /** This instance create an admin instance with provided adminID and userID. Only use this constructor for loading database. */
  Admin(std::string adminID, std::string userID);
  /** This constructor create an admin instance with provided user instance. */
  Admin(User user);

  // ------- Getters -------
  std::string getAdminID();
  std::string getUserID();

  // ------- Setters -------
  void setUserID(std::string userID);

  // ------- Other methods -------
  std::string toString();
  void save();
  User getUser();
  void getAdminByUser(User user);
};

#endif
