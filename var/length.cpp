// lentext.cc
#include "length.h"
#include <cstring>

//class LengthFieldBuffer 

// public members

// construct with a maximum of maxFields
LengthFieldBuffer :: LengthFieldBuffer ()
: VariableLengthBuffer()
{
	Init ();
}

// clear fields from buffer
void LengthFieldBuffer :: Clear ()
{
	VariableLengthBuffer::Clear ();
}

// set the value of the next field of the buffer;
// if size = -1 (default) use strlen(str) as length of field
// return number of bytes packed, -1 if error
int LengthFieldBuffer::Pack(const string& field)
{
	int len = field.size(); // length of string to be packed
	
	NextByte += (len + sizeof(len));
	Buffer.append(reinterpret_cast<const char*>(&len), sizeof(len));
	Buffer.append(field, len);
	BufferSize = NextByte;
	return len;
}

// extract the value of the next field of the buffer
// return the number of bytes extracted, -1 if error
int LengthFieldBuffer::Unpack(string& field)
{
	short len; // length of packed string
	if (NextByte >= BufferSize) return -1; // no more fields
	int start = NextByte; // first character to be unpacked

	len = *reinterpret_cast<const short*>(&Buffer[start]);
	NextByte += len + sizeof(len);

	if (NextByte > BufferSize) return -1;

	// Extract the string from the buffer
    field = Buffer.substr(start + sizeof(len), len);
	return len;
}

void LengthFieldBuffer :: Print (ostream & stream) const
{
	stream << "Buffer Size"<<BufferSize<<endl;
}


int LengthFieldBuffer :: Init ()
 // construct with a maximum of maxFields
{
	Initalized = true;
	Clear ();
	return true;
}

