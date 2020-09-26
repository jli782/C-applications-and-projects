/* Citation and Sources...
Final Project Milestone 6
Module: Vehicle
Filename: Vehicle.cpp
Version 1.0
Author	Jeffrey Li
Revision History
-----------------------------------------------------------
Date      Reason
2020/7/20 Preliminary release of Car module class definition
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/
#ifndef CAR_H
#define CAR_H
#include "Vehicle.h"
namespace sdds
{
	class Car :public Vehicle
	{
		bool m_carwash;
	public:
		Car();
		Car(const char* lp, const char* mm, bool carwash=false);
		Car(const Car&) = delete;
		Car& operator=(const Car&) = delete;
		std::istream& read(std::istream& is = std::cin);
		std::ifstream& read(std::ifstream& is);
		std::ostream& write(std::ostream& os = std::cout)const;
	};
}
#endif