#ifndef DATABASE_H
#define DATABASE_H

#include <vector>

#include "./User.h"
#include "./Member.h"

class Database
{
private:
  std::vector<User> users;
  /** This function is used to save the whole user list to file. */
  void saveUsersToFile();

  std::vector<Member> members;
  /** This function is used to save the whole member list to file. */
  void saveMembersToFile();

public:
  Database();

  // ------- User methods -------

  /** This function get all user in the database. */
  std::vector<User> getAllUsers();
  /** This function is used to get user by userID. */
  User *getUserByID(std::string userID);
  /** This function is used to add or update user in the database. */
  void saveUser(User *user);
  /** This function is used to remove a user from the database. */
  void removeUser(User user);

  // ------- Member methods -------

  /** This function get all member in the database. */
  std::vector<Member> getAllMembers();
  /** This function is used to get member by memberID. */
  Member *getMemberByID(std::string memberID);
  /** This function is used to add or update member in the database. */
  void saveMember(Member *member);
  /** This function is used to remove a member from the database. */
  void removeMember(Member member);
};

#endif