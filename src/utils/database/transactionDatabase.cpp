#include <unistd.h>

#include <fstream>
#include <iostream>
#include <vector>

#include "../../libs/Database.h"
#include "../../libs/Transaction.h"

void Database::saveTransactionsToFile()
{
  std::ofstream file("./data/transactions.txt", std::ios::trunc);
  for (int i = 0; i < this->transactions.size(); i++)
  {
    file << this->transactions[i].getTransactionID() << ", "
         << this->transactions[i].getBuyerID() << ", "
         << this->transactions[i].getSellerID() << ", "
         << this->transactions[i].getBidID() << ", "
         << this->transactions[i].getItemID() << ", "
         << this->transactions[i].getTransactionTime() << std::endl;
  }
  file.close();
}

std::vector<Transaction> Database::getAllTransactions()
{
  return this->transactions;
}

std::vector<Transaction> Database::getTransactionsByMemberID(
    std::string memberID)
{
  std::vector<Transaction> transactions;
  for (int index = 0; index < this->transactions.size(); index++)
  {
    if (this->transactions.at(index).getSellerID() == memberID ||
        this->transactions.at(index).getBuyerID() == memberID)
    {
      transactions.push_back(this->transactions.at(index));
    }
  }
  return transactions;
}

std::vector<Transaction> Database::getTransactionsByItemID(std::string itemID)
{
  std::vector<Transaction> transactions;
  for (int index = 0; index < this->transactions.size(); index++)
  {
    if (this->transactions.at(index).getItemID() == itemID)
    {
      transactions.push_back(this->transactions.at(index));
    }
  }
  return transactions;
}

void Database::saveTransaction(Transaction *transaction)
{
  bool isExist = false;
  for (int index = 0; index < this->transactions.size(); index++)
  {
    // If the transaction is exist in the database, update the transaction.
    if (this->transactions.at(index).getTransactionID() ==
        transaction->getTransactionID())
    {
      this->transactions.at(index) = *transaction;
      isExist = true;
      break;
    }
  }
  // If the transaction is not exist in the database, add it to the database.
  if (!isExist)
    this->transactions.push_back(*transaction);
  // Update the data in the file.
  this->saveTransactionsToFile();
}

void Database::removeTransaction(Transaction transaction)
{
  for (int index = 0; index < this->transactions.size(); index++)
  {
    if (this->transactions.at(index).getTransactionID() ==
        transaction.getTransactionID())
    {
      this->transactions.erase(this->transactions.begin() + index);
      break;
    }
  }
  // Update the data in the file.
  this->saveTransactionsToFile();
}
