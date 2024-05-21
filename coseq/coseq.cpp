// coseq.cpp
#include "coseq.h"

template <class ItemType>
CosequentialProcess<ItemType>::CosequentialProcess(int numberOfLists)
{	NumberOfLists = numberOfLists;}

template <class ItemType>
int CosequentialProcess<ItemType>::Match2Lists
	(char * List1Name, char * List2Name, char * OutputListName)
{
	int MoreItems;// true if items remain in lists
	InitializeList (1, List1Name);
	InitializeList (2, List2Name);
	InitializeOutput(OutputListName);
	MoreItems = NextItemInList(1) && NextItemInList(2);
	while (MoreItems){
		if (Item(1) < Item(2))
			MoreItems = NextItemInList(1);
		else if (Item(1) == Item(2)) // Item1 == Item2
		{
			ProcessItem (1); // match found
			MoreItems = NextItemInList(1) && NextItemInList(2);
		}
		else // Item(1) > Item(2)
			MoreItems = NextItemInList(2);
	}
	FinishUp();
	return 1;
}

template <class ItemType>
int CosequentialProcess<ItemType>::Merge2Lists
	(char * List1Name, char * List2Name, char * OutputListName)
{
	int MoreItems1, MoreItems2; // true if more items in list
	InitializeList (1, List1Name);
	InitializeList (2, List2Name);
	InitializeOutput (OutputListName);
	MoreItems1 = NextItemInList(1);
	MoreItems2 = NextItemInList(2);

	while (MoreItems1 || MoreItems2){// if either file has more
		if (Item(1) < Item(2))
		{// list 1 has next item to be processed
			ProcessItem (1); 
			MoreItems1 = NextItemInList(1);
		}
		else if (Item(1) == Item(2))
		{// lists have the same item, process from list 1
			ProcessItem (1);
			MoreItems1 = NextItemInList(1);
			MoreItems2 = NextItemInList(2);
		}
		else // Item(1) > Item(2)
		{// list 2 has next item to be processed
			ProcessItem (2);
			MoreItems2 = NextItemInList(2);
		}
	}
	FinishUp();
	return 1;
}
