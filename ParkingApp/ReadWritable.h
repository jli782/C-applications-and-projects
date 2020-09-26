/* Citation and Sources...
Final Project Milestone 6
Module: ReadWritable
Filename: ReadWritable.h
Version 1.0
Author	Jeffrey Li
Revision History
-----------------------------------------------------------
Date      Reason
2020/7/13 Member function declarations for ReadWritable class
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/
#ifndef READ_WRITABLE_H
#define READ_WRITABLE_H
#include <iostream>
#include <fstream>
#include "Utils.h"
//should force Read and Write capability to all its derived classes in two different ways; Comma Separated Values or Screen format. 
namespace sdds
{
	class ReadWritable
	{
		bool csvflag;
	public:
		ReadWritable();
		virtual ~ReadWritable();
		bool isCsv() const;
		void setCsv(bool value);
		virtual std::ostream& write(std::ostream& os = std::cout)const = 0;
		//The function will return a reference of an ostream and will receive a reference on an ostream as an optional argument. If this argument is not provided, the object “cout” will be passed instead. 
		
		virtual std::istream& read(std::istream& is = std::cin) = 0;
		//The function will return a reference of an istream and will receive a reference on an istream as an optional argument. If this argument is not provided, the object “cin” will be passed instead. 
		virtual std::ifstream& read(std::ifstream&) = 0;
	};
	std::ostream& operator<<(std::ostream& os, const ReadWritable& src);
	std::istream& operator>>(std::istream& os, ReadWritable& src);
	std::ifstream& operator>>(std::ifstream& is, ReadWritable& src);
}
#endif