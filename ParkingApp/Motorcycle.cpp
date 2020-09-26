/* Citation and Sources...
Final Project Milestone 6
Module: Motorcycle
Filename: Motorcycle.cpp
Version 1.0
Author	Jeffrey Li
Revision History
-----------------------------------------------------------
Date      Reason
2020/7/20 Preliminary implementation of Motorcycle module
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/

#include "Motorcycle.h"
namespace sdds
{
	Motorcycle::Motorcycle() :Vehicle(), m_sideCar(false)
	{
	}
	Motorcycle::Motorcycle(const char* lp, const char* mm, bool sideCar) : Vehicle(lp, mm), m_sideCar(sideCar)
	{
	}
	std::istream& Motorcycle::read(std::istream& is)
	{
		int sideCar = -1;
		if (isCsv()) { //if comma sep val
			Vehicle::read(is);
			is >> sideCar;
			is.ignore(100, '\n');
		}
		else {	//if not comma sep val, read normally
			std::cout << std::endl << "Motorcycle information entry" << std::endl;
			Vehicle::read(is);
			std::cout << "Does the Motorcycle have a side car? (Y)es/(N)o: ";
			sideCar = yesNoPrompt();
		}
		m_sideCar = sideCar == 1 ? true : false;
		return is;
	}
	std::ifstream& Motorcycle::read(std::ifstream& is)
	{
		int sideCar = -1;
		Vehicle::read(is);
		is >> sideCar;
		is.ignore(100, '\n');
		m_sideCar = sideCar == 1 ? true : false;
		return is;

	}
	std::ostream& Motorcycle::write(std::ostream& os)const
	{
		if (!isEmpty()) {
			isCsv() ? os << "m," : os << "Vehicle type: Motorcycle" << std::endl;
			Vehicle::write(os);
			if (isCsv()) {
				m_sideCar ? os << 1 << std::endl : os << 0 << std::endl;
			}
			else {
				m_sideCar ? os << "With Sidecar" << std::endl : os << ""; //std::endl;
			}
		}
		else {
			os << "Invalid Motorcycle Object" << std::endl;
		}
		return os;
	}
}