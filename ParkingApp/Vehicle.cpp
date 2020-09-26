/* Citation and Sources...
Final Project Milestone 6
Module: Vehicle
Filename: Vehicle.cpp
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
#include <cstring>
#include "Vehicle.h"
//#include "Utils.h"
namespace sdds
{
	void Vehicle::dynaAlloStr(const char* str)
	{
		if (checkValidString(str)) {
			m_makeModel = new char[strlen(str) + 1];
			strcpy(m_makeModel, str);
		}
		else {
			m_makeModel = nullptr;
		}
	}
	Vehicle::Vehicle()
	{
		setEmpty();
	}
	Vehicle::~Vehicle()
	{
		delete[] m_makeModel;
	}
	Vehicle::Vehicle(const char* lp, const char* mm)
	{
		if (checkValidString(lp) && strlen(lp) <= license && checkValidString(mm) && strlen(mm) >= 2) {
			m_parkingSpotNo = 0;
			//set m_makeModel and m_licensePlate
			setMakeModel(mm);
			strcpy(m_licensePlate, lp);
		}
		else {
			//if invalid, set to the Vehicle safe empty state 
			setEmpty();
		}
	}
	void Vehicle::setEmpty()
	{
		for (int i = 0; i <= license; i++) {
			m_licensePlate[i] = '\0';
		}
		dynaAlloStr("");
		m_parkingSpotNo = -1;
	}
	bool Vehicle::isEmpty() const
	{
		return m_parkingSpotNo == -1;
	}
	const char* Vehicle::getLicensePlate() const
	{
		return m_licensePlate;
	}
	const char* Vehicle::getMakeModel() const
	{
		return m_makeModel;
	}
	void Vehicle::setMakeModel(const char* mm)
	{
		checkValidString(mm) ? dynaAlloStr(mm) : dynaAlloStr(" ");
	}
	int Vehicle::getParkingSpot() const
	{
		return m_parkingSpotNo;
	}
	void Vehicle::setParkingSpot(int no)
	{
		m_parkingSpotNo = no >= 0 ? no : -1;
	}
	bool operator==(const Vehicle& v1, const char* licensePlate)
	{
		bool compare = checkValidString(licensePlate);
		if (compare) {
			char* tempLicense = new char[strlen(v1.getLicensePlate()) + 1];
			strcpy(tempLicense, v1.getLicensePlate());
			int length = strlen(tempLicense);

			for (int i = 0; i < length && compare; i++) {
				compare = toupper(tempLicense[i]) == toupper(licensePlate[i]);
			}
			delete[] tempLicense;
		}

		return compare;
	}
	bool operator==(const Vehicle& v1, const Vehicle& v2)
	{
		return v1 == v2.getLicensePlate();
	}
	std::istream& Vehicle::read(std::istream& is)
	{
		char licensePlate[license + 10] = { 0 };
		char* makeModel = nullptr;
		char s_makeModel[60 + 10] = { 0 };
		int parkingSpotNo = -1;
		if (isCsv()) {	//if Vehicle is set to csv mode
			is >> parkingSpotNo;
			is.ignore();
			is.get(licensePlate, 9, ',');
			is.ignore();

			is.get(s_makeModel, 61, ',');
			makeModel = new char[strlen(s_makeModel) + 1];
			strcpy(makeModel, s_makeModel);
			is.ignore(); //should drop the ',' from istream
		}
		else {	//if Vehicle NOT set to csv mode
			inputLicense(licensePlate, license + 10);
			inputMM(s_makeModel, 60 + 10);
			makeModel = new char[strlen(s_makeModel) + 1];
			strcpy(makeModel, s_makeModel);
			parkingSpotNo = 0;
		}
		if (is.fail()) {
			setEmpty();
		}
		else {
			delete[] m_makeModel;
			setMakeModel(makeModel);
			setParkingSpot(parkingSpotNo);
			uppercase(licensePlate);
			strcpy(m_licensePlate, licensePlate);

		}
		delete[] makeModel;
		makeModel = nullptr;
		return is;
	}
	std::ifstream& Vehicle::read(std::ifstream& is)
	{
		char licensePlate[license + 10] = { 0 };
		char* makeModel = nullptr;
		char s_makeModel[60 + 10] = { 0 };
		int parkingSpotNo = -1;
		is >> parkingSpotNo;
		is.ignore();
		is.get(licensePlate, 9, ',');
		is.ignore();

		is.get(s_makeModel, 61, ',');
		makeModel = new char[strlen(s_makeModel) + 1];
		strcpy(makeModel, s_makeModel);
		is.ignore(); //should drop the ',' from istream
		if (is.fail()) {
			setEmpty();
		}
		else {
			delete[] m_makeModel;
			setMakeModel(makeModel);
			setParkingSpot(parkingSpotNo);
			uppercase(licensePlate);
			strcpy(m_licensePlate, licensePlate);

		}
		delete[] makeModel;
		makeModel = nullptr;
		return is;
	}
	std::ostream& Vehicle::write(std::ostream& os)const
	{
		if (isEmpty()) {
			os << "Invalid Vehicle Object" << std::endl;
		}
		else {
			if (isCsv()) {
				os << m_parkingSpotNo;
				os << "," << m_licensePlate;
				os << "," << m_makeModel << ",";
			}
			else {
				os << "Parking Spot Number: ";
				m_parkingSpotNo == 0 ? os << "N/A" : os << m_parkingSpotNo;
				os << std::endl;
				os << "Licence Plate: " << m_licensePlate << std::endl;
				os << "Make and Model: " << m_makeModel << std::endl;
			}
		}

		return os;
	}
}