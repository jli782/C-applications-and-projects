/* Citation and Sources...
Final Project Milestone 6
Module: Vehicle
Filename: Vehicle.cpp
Version 1.0
Author	Jeffrey Li
Revision History
-----------------------------------------------------------
Date      Reason
2020/7/14 Preliminary declarations of Vehicle member functions and operators
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/
#ifndef VEHICLE_H
#define VEHICLE_H
#include "ReadWritable.h"

namespace sdds
{
	const int license = 8;
	class Vehicle : public ReadWritable
	{
		char m_licensePlate[license + 1]; 
		char* m_makeModel;	
		int m_parkingSpotNo;
		void dynaAlloStr(const char* str);
	public:
		Vehicle();
		~Vehicle();
		Vehicle(const char* lp, const char* mm);
		Vehicle(const Vehicle& src) = delete;
		Vehicle& operator=(const Vehicle& src) = delete;
		int getParkingSpot() const;		
		void setParkingSpot(int no);	

		std::istream& read(std::istream& is = std::cin);
		std::ostream& write(std::ostream& os = std::cout)const;
		std::ifstream& read(std::ifstream& is);
		friend bool operator==(const Vehicle& v1, const char* licensePlate);	
		friend bool operator==(const Vehicle& v1, const Vehicle& v2);	

	protected:
		void setEmpty();	
		bool isEmpty() const;		
		const char* getLicensePlate() const;
		const char* getMakeModel() const;	
		void setMakeModel(const char* mm);	
	};
}
#endif