#include "../libs/Member.h"
#include "../libs/User.h"
#include "../libs/IDGenerator.h"
#include "../libs/Database.h"

#include <iostream>
#include <regex>

#define MEMBER_ID_LENGTH 16
#define DEFAULT_FULLNAME ""
#define DEFAULT_PHONE_NUMBER ""
#define DEFAULT_EMAIL ""
#define DEFAULT_CREDIT_POINT 0
#define DEFAULT_RATING 0
#define DEFAULT_CREDIT 0

// ------- Constructors -------

Member::Member()
{
	this->memberID = IDGenerator::generateID(MEMBER_ID_LENGTH);
	this->fullname = DEFAULT_FULLNAME;
	this->phoneNumber = DEFAULT_PHONE_NUMBER;
	this->email = DEFAULT_EMAIL;
	this->creditPoint = DEFAULT_CREDIT_POINT;
	this->rating = DEFAULT_RATING;
	this->credit = DEFAULT_CREDIT;
}

Member::Member(std::string memberID, std::string fullname, std::string phoneNumber, std::string email, int creditPoint, float rating, int credit, std::string userID)
{
	this->memberID = memberID;
	this->fullname = fullname;
	this->phoneNumber = phoneNumber;
	this->email = email;
	this->creditPoint = creditPoint;
	this->rating = rating;
	this->credit = credit;
}

Member::Member(std::string fullname, std::string phoneNumber, std::string email, User user)
{
	this->memberID = IDGenerator::generateID(MEMBER_ID_LENGTH);
	this->fullname = fullname;
	this->phoneNumber = phoneNumber;
	this->email = email;
	this->creditPoint = DEFAULT_CREDIT_POINT;
	this->rating = DEFAULT_RATING;
	this->credit = DEFAULT_CREDIT;
	this->userID = user.getUserID();
}

// ------- Getters -------

std::string Member::getMemberID()
{
	return this->memberID;
}

std::string Member::getFullname()
{
	return this->fullname;
}

std::string Member::getPhoneNumber()
{
	return this->phoneNumber;
}

std::string Member::getEmail()
{
	return this->email;
}

int Member::getCreditPoint()
{
	return this->creditPoint;
}

float Member::getRating()
{
	return this->rating;
}

int Member::getCredit()
{
	return this->credit;
}

// ------- Setters -------

void Member::setFullname(std::string fullname)
{
	this->fullname = fullname;
}

void Member::setPhoneNumber(std::string phoneNumber)
{
	// Check if phone number is valid
	if (phoneNumber.length() < 10 || phoneNumber.length() > 12)
	{
		throw std::invalid_argument("Phone number must be between 10 and 12 characters.");
	}
	for (int index = 0; index < phoneNumber.length(); index++)
	{
		if (phoneNumber[index] < '0' || phoneNumber[index] > '9')
		{
			throw std::invalid_argument("Phone number must be a number.");
		}
	}
	// Check if phone number is unique
	std::vector<Member> members = Database().getAllMembers();
	for (int index = 0; index < members.size(); index++)
	{
		if (members[index].getPhoneNumber() == phoneNumber)
		{
			throw std::invalid_argument("This phone number is already used.");
		}
	}
	// Set phone number
	this->phoneNumber = phoneNumber;
}

void Member::setEmail(std::string email)
{
	// Check if email is valid using regex
	// Source: https://regexr.com/3e48o
	std::regex emailRegex("^[\\w-\\.]+@([\\w-]+\\.)+[\\w-]{2,4}$");
	if (!std::regex_match(email, emailRegex))
	{
		throw std::invalid_argument("Email is not valid.");
	}
	// Check if email is unique
	std::vector<Member> members = Database().getAllMembers();
	for (int index = 0; index < members.size(); index++)
	{
		if (members[index].getEmail() == email)
		{
			throw std::invalid_argument("This email address is already used.");
		}
	}
	this->email = email;
}

void Member::setCreditPoint(int creditPoint)
{
	this->creditPoint = creditPoint;
}

void Member::setRating(float rating)
{
	this->rating = rating;
}

void Member::setCredit(int credit)
{
	this->credit = credit;
}

std::string Member::getUserID()
{
	// Check if user ID is existed
	std::vector<User> users = Database().getAllUsers();
	for (int index = 0; index < users.size(); index++)
	{
		if (users[index].getUserID() == this->userID)
		{
			return this->userID;
		}
	}
	throw std::invalid_argument("User ID is not existed.");
}

// ------- Other methods -------

std::string Member::toString()
{
	return "Member ID: " + this->memberID + ", Fullname: " + this->fullname + ", Phone number: " + this->phoneNumber + ", Email: " + this->email + ", Credit point: " + std::to_string(this->creditPoint) + ", Rating: " + std::to_string(this->rating) + ", Credit: " + std::to_string(this->credit) + ", User ID: " + this->userID;
}

User Member::getUser()
{
	std::vector<User> users = Database().getAllUsers();
	for (int index = 0; index < users.size(); index++)
	{
		if (users[index].getUserID() == this->userID)
		{
			return users[index];
		}
	}
	throw std::invalid_argument("User ID does not exist.");
}

void Member::save()
{
	Database().saveMember(this);
}