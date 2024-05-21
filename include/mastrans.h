// mastrans.h
#ifndef MASTRANS_H
#define MASTRANS_H

#include "coseq.h"
#include "../coseq/coseq.cpp"  // for template

// a cosequential process that supports master/transaction processing
template <class ItemType>
class MasterTransactionProcess: public CosequentialProcess<ItemType>
{
public:
	MasterTransactionProcess ();//constructor
	// when new master read
	virtual int ProcessNewMaster ()=0;
	// each transaction for a master
	virtual int ProcessCurrentMaster ()=0;
	// after all transactions for a master
	virtual int ProcessEndMaster ()=0;
	// no master for transaction
	virtual int ProcessTransactionError ()=0;

	// cosequential processing of master and transaction records
	int PostTransactions 
		(char * MasterFileName, char * TransactionFileName, 
			char * OutputListName);
};


#endif
