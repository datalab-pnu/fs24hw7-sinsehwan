// coseq.h
#ifndef COSEQ_H
#define COSEQ_H

// base class for cosequential processing
template <class ItemType>
class CosequentialProcess
{
public:
	CosequentialProcess(int numberOfLists);

	// The following methods provide basic list processing
	// These must be defined in subclasses
	virtual int InitializeList (int ListNumber, char * ListName)=0;
	virtual int InitializeOutput (char * OutputListName)=0;
	virtual int NextItemInList (int ListNumber)=0; 
	//advance to next item in this list
	virtual ItemType Item (int ListNumber) = 0; 
	// return current item from this list
	virtual int ProcessItem (int ListNumber)=0; // process the item in this list
	virtual int FinishUp()=0; // complete the processing

	// General list processing methods
	virtual int Match2Lists (char * List1Name, char * List2Name, char * OutputListName);
	// 2-way sequential matching algorithm
	virtual int Merge2Lists (char * List1Name, char * List2Name, char * OutputListName);
	// 2-way sequential merging algorithm
protected:
	int NumberOfLists; // number of lists to be processed
};

#endif
