/* Citation and Sources...
Final Project Milestone 6
Module: Vehicle
Filename: Vehicle.cpp
Version 1.0
Author	Jeffrey Li
Revision History
-----------------------------------------------------------
Date      Reason
2020/7/20 Preliminary definition of Motorcycle module
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/
#ifndef MOTORCYCLE_H
#define MOTORCYCLE_H
#include "Vehicle.h"
namespace sdds
{
	class Motorcycle :public Vehicle
	{
		bool m_sideCar;
	public:
		Motorcycle();
		Motorcycle(const char* lp, const char* mm, bool sideCar = false);
		Motorcycle(const Motorcycle&) = delete;
		Motorcycle& operator=(const Motorcycle&) = delete;
		std::istream& read(std::istream& is = std::cin);
		std::ifstream& read(std::ifstream& is);
		std::ostream& write(std::ostream& os = std::cout)const;
	};
}
#endif