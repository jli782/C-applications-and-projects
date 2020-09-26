/* Citation and Sources...
Final Project Milestone 6
Module: Parking
Filename: Parking.cpp
Version 1.0
Author	Jeffrey Li
Revision History
-----------------------------------------------------------
Date      Reason
2020/7/14 Preliminary definitions of Vehicle member functions and operators
2020/7/20 Updated read to accomodate for while loop validation
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/
#ifndef __PARKING__
#define __PARKING__
#include "Menu.h"
#include "Car.h"
#include "Motorcycle.h"
namespace sdds
{
	const int maxParkingSpots = 100;
	
	class Parking 
	{
		int m_noOfSpots; //always less than maxParkingSpots
		int m_noOfParkedVehicles; //always less than noOfSpots
		Vehicle* m_parkingSpots[maxParkingSpots];
		char* filename;
		Menu parkingMenu;
		Menu vehicleSelectionMenu;
		void dynaAllocFilename(const char* original);
		bool isEmpty();
		Parking(const Parking&) = delete;
		Parking& operator=(const Parking&) = delete;
		void parkingStatus();
		void parkVehicle();
		void returnVehicle();
		void listParkedVehicles();
		bool closeParking();
		bool exitParkingApp();
		bool loadDataFile();
		void saveDataFile();
	public:
		Parking(const char* datafile, int noOfSpots);
		Parking(const char* str);
		virtual ~Parking();
		int run();
	};
}
#endif