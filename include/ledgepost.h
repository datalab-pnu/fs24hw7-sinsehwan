// ledgpost.h

#pragma once
#ifndef LEDGPOST_H
#define LEDGPOST_H


#include "mastrans.h"
#include "student.h"
#include "courseRegistration.h"
#include "recfile.h"
#include "length.h"

#include "../buf/recfile.cpp"  // for template
#include "../coseq/mastrans.cpp"  // for template

// ledger processing of a ledger file and a journal file
// the item type is int to represent an account number
class LedgerProcess: public MasterTransactionProcess<int>
{
public:
	LedgerProcess(int semesterNumber); // constructor

	// Basic list processing methods
	int InitializeList (int ListNumber, char * List1Name);
	int InitializeOutput (char * OutputListName);
	int NextItemInList (int ListNumber); //get next item from this list
	int Item (int ListNumber); // return current item from this list
	int ProcessItem (int ListNumber); // process the item in this list
	int FinishUp(); // complete the processing

	// master/transaction methods
	virtual int ProcessNewMaster ();//  when new master read
	virtual int ProcessCurrentMaster ();// each transaction for a master
	virtual int ProcessEndMaster ();// after all transactions for a master
	virtual int ProcessTransactionError ();// no master for transaction

protected:
	// members
	int SemesterNumber; // number of month to be processed
	LengthFieldBuffer Sbuffer, Cbuffer; // buffers for files
	RecordFile<Student> StudentFile; // list 1 //원래 ledger
	RecordFile<CourseRegistration> CRFile;// list 2 // 원래 journal
	int AccountNumber [3]; // current item in each list
	Student student; // current ledger object
	CourseRegistration cr; // current journal object
	ofstream OutputList; // text output file for post method
	static int LowAcct;// lower than the lowest account number
	static int HighAcct;// higher than the highest account number

	int NextItemInLedger ();
	int NextItemInJournal ();
};

//#include "../ledgepost/ledgepost.cpp"

#endif
