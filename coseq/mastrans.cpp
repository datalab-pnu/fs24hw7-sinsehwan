// mastrans.cpp
#include "mastrans.h"

template <class ItemType>
MasterTransactionProcess<ItemType>::MasterTransactionProcess ()
: CosequentialProcess<int>(2)
{}

// Item(1): always stores the current master record
// Item(2): always stores the current transactions record
template <class ItemType>
int MasterTransactionProcess<ItemType>::PostTransactions 
	(char * MasterFileName, char * TransactionFileName, char * OutputListName)
{
	int MoreMasters, MoreTransactions; // true if more items in particular list
	this->InitializeList (1, MasterFileName);
	this->InitializeList (2, TransactionFileName);
	this->InitializeOutput (OutputListName);
	MoreMasters = this->NextItemInList(1);
	MoreTransactions = this->NextItemInList(2);
	if (MoreMasters) ProcessNewMaster(); // process first master

	while (MoreMasters || MoreTransactions){// if either file has more
		if (this->Item(1) < this->Item(2))
		{// finish this master record
			ProcessEndMaster();
			MoreMasters = this->NextItemInList(1);
			// If read successful, then print title line for new account
			if (MoreMasters) ProcessNewMaster(); 
		}
		else if (this->Item(1) == this->Item(2)) // Transaction matches Master
		{
			ProcessCurrentMaster(); // another transaction for the master
			this->ProcessItem (2);// output transaction record
			MoreTransactions = this->NextItemInList(2);
		}
		else // Item(1) > Item(2)
		{// transaction with no master
			ProcessTransactionError();
			MoreTransactions = this->NextItemInList(2);
		}
	}
	this->FinishUp();
	return 1;
}

