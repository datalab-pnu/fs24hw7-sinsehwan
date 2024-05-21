#include <iostream>

#include <string.h>
#include "recfile.h"
#include "length.h"
#include "ledgepost.h"
// commented due to the repeated definition
//#include "./coseq/mastrans.cpp"  // for template
//#include "testSetting.cpp"

using namespace std;

Student * S[12];
CourseRegistration *C[10];

void LedgerWrite (IOBuffer & Buff, char * myfile)
{
	S[0] = new Student(1, "ajsggs", "sf", Date(5, 4), 20);
	S[1] = new Student(2,"Check", "sg", Date(6, 3), 20);	
	S[2] = new Student(3,"Adver", "sho", Date(2, 3), 40);
	S[3] = new Student(4,"Auto", "asdg", Date(3, 2), 30);
	S[4] = new Student(5,"harges", "shh", Date(7, 1), 100);
	S[5] = new Student(6,"Books", "goi", Date(12, 2), 25);
	S[6] = new Student(7,"expense", "hidso", Date(10, 29), 120);
	S[7] = new Student(8,"Mis", "iwue", Date(8, 5), 12);
	S[8] = new Student(9,"Offize", "sgsf", Date(6, 7), 18);
	S[9] = new Student(10,"Postage", "spg", Date(4, 4), 24);
	S[10] = new Student(11,"Rent", "asdf", Date(10, 7), 79);
	S[11] = new Student(12,"Supplies", "bwg", Date(11, 3), 68);	

	// Ledger File
	RecordFile<Student> studentFile(Buff);
	studentFile.Create(myfile,ios::out|ios::in);
	for (int i= 0; i<12; i++)
	{
		studentFile.Write(*S[i]);
	} 
	studentFile.Close();
}

void LedgerRead (IOBuffer & Buff, char * myfile)
{
	int res;

	RecordFile<Student> sFile(Buff);
	sFile.Open(myfile, ios::in);
	Student student;
	cout<<"Student Samples================================" << endl;
	// ledger.PrintHeader(cout); weird
	while (1)
	{
		res=sFile.Read(student);
		if (res<=0) break;
		student.Print(cout);
	}
	cout <<endl;
}


void JournalWrite (IOBuffer & Buff, char * myfile)
{
	C[0] = new CourseRegistration(101, 3, 1);
	C[0]->addStudent(*S[0]);
	C[0]->addStudent(*S[1]);
	C[0]->addStudent(*S[3]);
	C[1] = new CourseRegistration(102, 4, 2);
	C[1]->addStudent(*S[0]);
	C[1]->addStudent(*S[2]);
	C[1]->addStudent(*S[4]);
	C[2] = new CourseRegistration(103, 2, 2);
	C[2]->addStudent(*S[1]);
	C[2]->addStudent(*S[3]);
	C[2]->addStudent(*S[4]);
	C[3] = new CourseRegistration(104, 3, 1);
	C[0]->addStudent(*S[3]);
	C[0]->addStudent(*S[5]);
	C[0]->addStudent(*S[7]);
	C[4] = new CourseRegistration(105, 2, 4);
	C[4]->addStudent(*S[4]);
	C[4]->addStudent(*S[6]);
	C[4]->addStudent(*S[8]);
	C[5] = new CourseRegistration(106, 3, 3);
	C[5]->addStudent(*S[3]);
	C[5]->addStudent(*S[8]);
	C[5]->addStudent(*S[9]);
	C[6] = new CourseRegistration(107, 3, 2);
	C[6]->addStudent(*S[0]);
	C[6]->addStudent(*S[1]);
	C[6]->addStudent(*S[2]);
	C[7] = new CourseRegistration(108, 2, 1);
	C[7]->addStudent(*S[1]);
	C[7]->addStudent(*S[3]);
	C[7]->addStudent(*S[5]);
	C[8] = new CourseRegistration(109, 3, 2);
	C[8]->addStudent(*S[0]);
	C[8]->addStudent(*S[1]);
	C[8]->addStudent(*S[4]);
	C[9] = new CourseRegistration(110, 4, 3);
	C[9]->addStudent(*S[7]);
	C[9]->addStudent(*S[8]);
	C[9]->addStudent(*S[9]);

	// Ledger File
	RecordFile<CourseRegistration> crFile(Buff);
	crFile.Create(myfile,ios::out|ios::in);
	for (int i= 0; i<10; i++)
	{
		crFile.Write(*C[i]);
	} 
	crFile.Close();
}

void JournalRead (IOBuffer & Buff, char * myfile)
{
	int res;
	RecordFile<CourseRegistration> crFile(Buff);
	crFile.Open(myfile, ios::in);
	CourseRegistration cr;
	cout << "courseRegistration Entries =======================>" << endl;
	//journal.PrintHeader();
	while (1)
	{
		res=crFile.Read(cr);
		if (res<=0) break;
		cr.printStudentLine(cout);
	}
	cout << endl;
}



int setting()
{
	LengthFieldBuffer Lbuffer;
	LedgerWrite(Lbuffer,"student.dat");

	LengthFieldBuffer Jbuffer;
	JournalWrite(Jbuffer, "cr.dat");

	LedgerRead(Lbuffer,"student.dat");
	JournalRead(Jbuffer, "cr.dat");
	
}

int main()
{
	setting();
	const int semester = 2; // processing for April

	LedgerProcess Posting(semester);		// LedgerProcess for April
	// master for ledger, transact for journal
	//Posting.PostTransactions("ledger.dat","journal.dat","report.txt");
	Posting.PostTransactions("student.dat","cr.dat","report.txt");
	return 1;
}
