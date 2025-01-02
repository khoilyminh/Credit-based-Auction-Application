#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include <vector>
#include "User.h"

class Member
{
private:
	std::string memberID;
	std::string fullname;
	std::string phoneNumber;
	std::string email;
	int creditPoint;
	float rating;
	int credit;
	std::string userID;

public:
	// ------- Constructors -------

	/** This constructor create a blank member instance. */
	Member();
	/** This constructor create a member instance with provide parameters. Only use this constructor for loading from database. */
	Member(std::string memberID, std::string fullname, std::string phoneNumber, std::string email, int creditPoint, float rating, int credit, std::string userID);
	/** This constructor create a member instance with provide parameters. Use this for create new memeber. */
	Member(std::string fullname, std::string phoneNumber, std::string email, User user);

	// ------- Getters -------

	/** Get member ID. */
	std::string getMemberID();
	/** Get member full name. */
	std::string getFullname();
	/** Get member phone number. */
	std::string getPhoneNumber();
	/** Get member email. */
	std::string getEmail();
	/** Get member credit point. */
	int getCreditPoint();
	/** Get member rating. */
	float getRating();
	/** Get member reviews. */
	std::vector<std::string> getReviews();
	/** Get member credit. */
	int getCredit();
	/** Get user ID. */
	std::string getUserID();

	// ------- Setters -------
	/** This function is used to set the fullname of member instance. */
	void setFullname(std::string fullname);
	/** This function is used to set the phone number of member instance. */
	void setPhoneNumber(std::string phoneNumber);
	/** This function is used to set the email of member instance. */
	void setEmail(std::string email);
	/** This function is used to set the credit point of member instance. */
	void setCreditPoint(int creditPoint);
	/** This function is used to set the rating of member instance. */
	void setRating(float rating);
	/** This function is used to set the credit of member instance. */
	void setCredit(int credit);

	// ------- Other methods -------
	/** This method will print out the information of member instance. */
	void print();
	/** This method will convert the member instance to string. */
	std::string toString();
	/** This method will get the user instance of the memeber instance. */
	User getUser();
	/** This method will save the member instance to the database. */
	void save();
};

#endif
