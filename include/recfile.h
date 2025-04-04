#ifndef RECFILE_H
#define RECFILE_H

#include "buffile.h"
#include "ioBuffer.h"


// template class to support direct read and write of records
// The template parameter RecType must support the following
//	int Pack (BufferType &); pack record into buffer
//	int Unpack (BufferType &); unpack record from buffer

template <class RecType>
class RecordFile: public BufferFile
{
public:
	int Read(RecType & record, int recaddr = -1);
	int Write(const RecType & record, int recaddr = -1);
	int Append(const RecType & record, int recaddr = -1);
	RecordFile (IOBuffer & buffer): BufferFile (buffer) {}
};


// this is for template
//#include "../buf/recfile.cpp"

// template method bodies
/*
template <class RecType>
int RecordFile<RecType>::Read(RecType & record, int recaddr)
{
	int readAddr, result;
	readAddr = BufferFile::Read (recaddr);
	if (readAddr==-1) return -1;
	result = record . Unpack (Buffer);
	if (!result) return -1;
	return readAddr;
}

template <class RecType>
int RecordFile<RecType>::Write(const RecType & record, int recaddr)
{
	int result;
	result = record . Pack (Buffer);
	if (!result) return -1;
	return BufferFile::Write (recaddr);
}

template <class RecType>
int RecordFile<RecType>::Append(const RecType & record, int recaddr)
{
	int result;
	result = record . Pack (Buffer);
	if (!result) return -1;
	return BufferFile::Append ();
}
*/


#endif