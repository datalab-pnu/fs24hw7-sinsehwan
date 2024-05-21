#include "ledgepost.h"
//#include "../coseq/mastrans.cpp" // for template
//#include "../coseq/coseq.cpp"
//#include "../include/mastrans.h"
//#include "coseq.h"

// list processing methods

LedgerProcess::LedgerProcess(int semesterNumber)
: MasterTransactionProcess<int>(), StudentFile(Sbuffer), CRFile(Cbuffer)
{
	SemesterNumber = semesterNumber;
}

int LedgerProcess::InitializeList(int ListNumber, char * ListName)
{
	AccountNumber[ListNumber] = LowAcct;
	switch (ListNumber)
	{
		case 1: // initialize ledger file
			return StudentFile.Open(ListName, ios::in);
		case 2: // initialize ledger file
			return CRFile.Open(ListName, ios::in);
	}
	return FALSE;
}

int LedgerProcess::InitializeOutput (char * OutputListName)
{
	OutputList.open(OutputListName);
	return 1;
}

int LedgerProcess::NextItemInList (int ListNumber)
//get next item from this list
{
	switch (ListNumber)
	{
		case 1: return NextItemInLedger ();
		case 2: return NextItemInJournal ();
	}
	return FALSE;
}

int LedgerProcess::Item (int ListNumber)
// return current item from this list
{	return AccountNumber[ListNumber];}

int LedgerProcess::ProcessItem (int ListNumber)
// process the item in this list when it first appears
{
	switch (ListNumber)
	{
		case 1: // process new student object
			student.Print(OutputList);
		case 2: // process courseRegistration file
			cr.printStudentLine(OutputList, student.getID(), SemesterNumber);
	}
	return TRUE;
}

int LedgerProcess::ProcessNewMaster ()//  when new master read
{// first step in proceesing master record
 // print the header and setup last month's balance
	student.Print(OutputList);
	//ledger.Balances[MonthNumber] = ledger.Balances[MonthNumber-1];
	return TRUE;
}

int LedgerProcess::ProcessCurrentMaster ()// each transaction for a master
{// add the transaction amount to the balance for this month	
	//ledger.Balances[MonthNumber] += journal.Amount;
	return TRUE;
}

int LedgerProcess::ProcessEndMaster ()// after all transactions for a master
{// print the balances line to output	
	//PrintBalances(OutputList,ledger.Balances[MonthNumber-1],ledger.Balances[MonthNumber]);
	return TRUE;
}

int LedgerProcess::ProcessTransactionError ()// no master for transaction
{// print error message to standard error
	cerr<<"Error no account for journal"<<endl;
	cerr<<cr.getCourseID(); 
	return TRUE;
}

int LedgerProcess::FinishUp()
// complete the processing
{
	StudentFile.Close(); 
	CRFile.Close(); 
	OutputList.close();
	return TRUE;
}

int LedgerProcess::NextItemInLedger ()
{
	int res = StudentFile . Read (student);
	if (res <= 0) 
	{
		AccountNumber[1] = HighAcct;
		return FALSE;
	}
	if (student.getID() <= AccountNumber[1])
	{	cerr<<"student id out of order"<<endl; exit(0);}
	AccountNumber[1]=student.getID();
	return TRUE;
}

int LedgerProcess::NextItemInJournal ()
{
	int nextSID = cr.getNextSID();
	if (nextSID == -1)
	{
		int res = CRFile.Read(cr);
		if (res <= 0) 
		{
			AccountNumber[2] = HighAcct;
			return FALSE;
		}
		nextSID = cr.getNextSID();
	}
	if (nextSID < AccountNumber[2])
	{	cerr<<"course registration out of order"<<endl; exit(0);}
	AccountNumber[2]=nextSID;
	return TRUE;
}

int LedgerProcess::LowAcct = -1;
int LedgerProcess::HighAcct = 9999;