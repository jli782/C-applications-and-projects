/* Citation and Sources...
Final Project Milestone 6
Module: Car
Filename: Car.cpp
Version 1.0
Author	Jeffrey Li
Revision History
-----------------------------------------------------------
Date      Reason
2020/7/20 initial commit of implementation of Car module
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/
#include "Car.h"

namespace sdds
{
	Car::Car() :Vehicle(), m_carwash(false)
	{
	}
	Car::Car(const char* lp, const char* mm, bool carwash) : Vehicle(lp, mm), m_carwash(carwash)
	{
	}
	std::istream& Car::read(std::istream& is)
	{
		int carwash = -1;
		if (isCsv()) {	//if is comma sep val
			Vehicle::read(is);
			is >> carwash;
			is.ignore(1000, '\n');
		}
		else {
			//read as normally
			std::cout << std::endl << "Car information entry" << std::endl;
			Vehicle::read(is);
			std::cout << "Carwash while parked? (Y)es/(N)o: ";
			carwash = yesNoPrompt();
		}
		m_carwash = carwash == 1 ? true : false;
		return is;
	}
	std::ifstream& Car::read(std::ifstream& is)
	{
		int carwash = -1;
		Vehicle::read(is);
		is >> carwash;
		is.ignore(1000, '\n');
		m_carwash = carwash == 1 ? true : false;
		return is;
	}
	std::ostream& Car::write(std::ostream& os)const
	{
		if (!isEmpty()) {
			isCsv() ? os << "c," : os << "Vehicle type: Car" << std::endl;
			Vehicle::write(os);
			if (isCsv()) {
				m_carwash ? os << 1 << std::endl : os << 0 << std::endl;
			}
			else {
				m_carwash ? os << "With Carwash" << std::endl : os << "Without Carwash" << std::endl;
			}
		}
		else {
			os << "Invalid Car Object" << std::endl;
		}
		return os;
	}
}