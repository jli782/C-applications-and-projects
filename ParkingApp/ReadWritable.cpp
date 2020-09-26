/* Citation and Sources...
Final Project Milestone 6
Module: ReadWritable
Filename: ReadWritable.cpp
Version 1.0
Author	Jeffrey Li
Revision History
-----------------------------------------------------------
Date      Reason
2020/7/13 Testing ReadWritable module, added preliminary member functions, virutal functions
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/
#include "ReadWritable.h"
using namespace std;
namespace sdds
{
	ReadWritable::ReadWritable()
	{
		csvflag = false;
	}
	ReadWritable::~ReadWritable()
	{
	}
	bool ReadWritable::isCsv() const
	{
		return csvflag;
	}
	void ReadWritable::setCsv(bool value)
	{
		csvflag = value;
	}
	ostream& operator<<(ostream& os, const ReadWritable& src)
	{
		src.write(os);
		return os;
	}
	istream& operator>>(istream& is, ReadWritable& src)
	{
		src.read(is);
		return is;
	}
	std::ifstream& operator>>(std::ifstream& is, ReadWritable& src)
	{
		src.read(is);
		return is;
	}
}