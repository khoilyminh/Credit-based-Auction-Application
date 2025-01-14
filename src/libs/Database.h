#ifndef DATABASE_H
#define DATABASE_H

#include <vector>

#include "./User.h"
#include "./Member.h"
#include "./Admin.h"
#include "./Item.h"

class Database
{
private:
  std::vector<User> users;
  /** This function is used to save the whole user list to file. */
  void saveUsersToFile();

  std::vector<Member> members;
  /** This function is used to save the whole member list to file. */
  void saveMembersToFile();

  std::vector<Admin> admins;
  /** This function is used to save the whole admin list to file. */
  void saveAdminsToFile();

  std::vector<Item> items;
  /** This function is used to save the whole member list to file. */
  void saveItemsToFile();

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

  // ------- Admin methods -------

  /** This function get all admin in the database. */
  std::vector<Admin> getAllAdmins();
  /** This function is used to get admin by adminID. */
  Admin *getAdminByID(std::string adminID);
  /** This function is used to add or update admin in the database. */
  void saveAdmin(Admin *admin);
  /** This function is used to remove a admin from the database. */
  void removeAdmin(Admin admin);

  // ------- Item Methods -------

  /** This function get all member in the database. */
  std::vector<Item> getAllItems();
  /** This function is used to get member by itemID. */
  Item *getItemByID(std::string itemID);
  /** This function is used to add or update an Item in the database. */
  void saveItem(Item *item);
  /** This function is used to remove an Item from the database. */
  void removeItem(Item item);
};

#endif