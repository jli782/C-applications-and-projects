/* Citation and Sources...
Final Project Milestone 6
Module: Parking
Filename: Parking.cpp
Version 2.0
Author	Jeffrey Li
Revision History
-----------------------------------------------------------
Date      Reason
2020/7/7  Preliminary release
2020/7/10  Debugged DMA
2020/8/4  Review and testing of read and write functionality
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/
#include <iomanip>
#include <cstring>
#include "Parking.h"
//#include "Utils.h"
using namespace std;

namespace sdds
{
	Parking::Parking(const char* datafile, int noOfSpots)
	{
		m_noOfParkedVehicles = 0;
		m_noOfSpots = noOfSpots;
		for (int i = 0; i < maxParkingSpots; i++) {
			m_parkingSpots[i] = nullptr;
		}
		if (m_noOfSpots < 10 || m_noOfSpots > maxParkingSpots) {
			filename = nullptr;
		}
		else {
			if (checkValidString(datafile)) {
				filename = new char[strlen(datafile) + 1];
				strcpy(filename, datafile);
			}
			else {
				filename = nullptr;
			}
			if (loadDataFile()) {
				//populate parkingMenu
				Menu temp("Parking Menu, select an action:");
				temp << "Park Vehicle" << "Return Vehicle" << "List Parked Vehicles" << "Close Parking (End of day)" << "Exit Program";
				parkingMenu = temp;

				//populate vehicleSelectionMenu
				Menu temp2("Select type of the vehicle:", 1);
				temp2 << "Car" << "Motorcycle" << "Cancel";
				vehicleSelectionMenu = temp2;
			}
			else {
				cout << "Error in data file" << endl;
			}

		}
	}
	Parking::Parking(const char* str) :filename(nullptr)
	{
		if (checkValidString(str)) {
			dynaAllocFilename(str);
		}
		else {
			filename = nullptr;
		}
		//call loadDataFile(), if true, populate Parking and Vehicle menus dt mem; if false, print "Error in data file"<NEWLINE> and set to invalid empty state
		if (loadDataFile()) {
			//populate parkingMenu
			Menu temp("Parking Menu, select an action:");
			temp << "Park Vehicle" << "Return Vehicle" << "List Parked Vehicles" << "Close Parking (End of day)" << "Exit Program";
			parkingMenu = temp;

			//populate vehicleSelectionMenu
			Menu temp2("Select type of the vehicle:", 1);
			temp2 << "Car" << "Motorcycle" << "Cancel";
			vehicleSelectionMenu = temp2;
		}
		else {
			cout << "Error in data file" << endl;
		}
	}
	Parking::~Parking()
	{
		saveDataFile();
		delete[] filename;
		filename = nullptr;
		for (int i = 0; i < m_noOfSpots; i++) {
			delete m_parkingSpots[i];
			m_parkingSpots[i] = nullptr;
		}
	}
	bool Parking::isEmpty()
	{
		return !checkValidString(filename);
	}
	void Parking::parkingStatus()
	{
		cout << "****** Seneca Valet Parking ******" << endl << "*****  Available spots: " << setw(4) << left << m_noOfSpots - m_noOfParkedVehicles << right << " *****" << endl;
	}
	void Parking::parkVehicle()
	{
		if (m_noOfParkedVehicles == m_noOfSpots) { //m_noOfSpots <= 0
			cout << "Parking is full" << endl;
		}
		else {
			Vehicle* temp = nullptr;
			switch (vehicleSelectionMenu.run()) {
			case 1:
				temp = new Car();
				break;
			case 2:
				temp = new Motorcycle();
				break;
			case 3:
				cout << "Parking cancelled" << endl;
				break;
			}
			bool notEmpty;
			notEmpty = true;
			if (temp != nullptr) {
				for (int i = 0; i < m_noOfSpots && notEmpty; i++) {
					if (m_parkingSpots[i] == nullptr) {
						m_parkingSpots[i] = temp;
						m_parkingSpots[i]->setCsv(false);
						m_parkingSpots[i]->read();
						m_parkingSpots[i]->setParkingSpot(i + 1);
						notEmpty = false;
						cout << endl << "Parking Ticket" << endl << *(m_parkingSpots[i]) << endl;
					}
				}
				m_noOfParkedVehicles++;
			}

		}
	}
	void Parking::returnVehicle()
	{
		cout << "Return Vehicle" << endl;
		char vLicensePlate[license + 10] = { 0 };
		inputLicense(vLicensePlate, license + 10);
		uppercase(vLicensePlate);
		bool match = false;
		for (int i = 0; i < m_noOfSpots && !match; i++) {
			if (*(m_parkingSpots[i]) == vLicensePlate) {
				match = true;
				m_parkingSpots[i]->setCsv(false);
				cout << endl << "Returning: " << endl << *(m_parkingSpots[i]) << endl;
				delete m_parkingSpots[i];
				m_parkingSpots[i] = nullptr;
				m_noOfParkedVehicles--;
			}
		}
		if (!match) {
			cout << "License plate " << vLicensePlate << " Not found" << endl;
		}

	}
	void Parking::listParkedVehicles()
	{
		cout << "*** List of parked vehicles ***" << endl;
		for (int i = 0; i < m_noOfSpots; i++) {
			if (m_parkingSpots[i] != nullptr) {
				m_parkingSpots[i]->setCsv(false);
				cout << *(m_parkingSpots[i]) << "-------------------------------" << endl;
			}
		}
	}
	bool Parking::closeParking()
	{
		bool val = true;
		if (isEmpty()) { //m_noOfSpots <= 0
			cout << "Closing Parking" << endl;
		}
		else {
			cout << "This will Remove and tow all remaining vehicles from the parking!" << endl << "Are you sure? (Y)es/(N)o: ";
			if (yesNoPrompt() == 0) {
				cout << "Aborted!" << endl;
				val = false;
			}
			else {
				cout << "Closing Parking" << endl;
				for (int i = 0; i < m_noOfSpots; i++) {
					if (m_parkingSpots[i] != nullptr) {
						m_parkingSpots[i]->setCsv(false);
						cout << endl << "Towing request" << endl << "*********************" << endl << *(m_parkingSpots[i]);// << endl;
						delete m_parkingSpots[i];
						m_parkingSpots[i] = nullptr;
					}
				}
			}
		}

		return val;
	}
	bool Parking::exitParkingApp()
	{
		cout << "This will terminate the program!" << endl << "Are you sure? (Y)es/(N)o: ";
		bool value = yesNoPrompt() == 1;
		return value;
	}
	void Parking::dynaAllocFilename(const char* original)
	{
		if (original == nullptr) {
			filename = new char[1];
			filename[0] = 0;
		}
		else {
			delete[] filename;
			filename = new char[strlen(original) + 1];
			strcpy(filename, original);
		}
	}
	bool Parking::loadDataFile()
	{
		bool valid = false;
		ifstream file;
		if (!isEmpty()) {
			valid = true;
			file.open(filename);
			if (!file.is_open() || isEmpty()) {
				valid = true;
			}
			else {
				while (file && valid && m_noOfParkedVehicles < m_noOfSpots) {
					Vehicle* temp = nullptr;
					char label = 'z';
					file.get(label);
					file.ignore();
					label = toupper(label);
					if (label == 'M') {
						temp = new Motorcycle();
					}
					else if (label == 'C') {
						temp = new Car();
					}
					if (temp != nullptr) {
						temp->setCsv(true);
						if (temp->read(file)) {
							m_parkingSpots[temp->getParkingSpot() - 1] = temp;
							m_noOfParkedVehicles++;
						}
						else {
							delete temp;
							valid = false;
						}
					}
				}
			}
			valid = true;
		}
		return valid;
	}
	void Parking::saveDataFile()
	{
		ofstream file(filename);
		if (file.is_open()) {
			for (int i = 0; i < m_noOfSpots; i++) {
				if (m_parkingSpots[i] != nullptr) {
					m_parkingSpots[i]->setCsv(true);
					m_parkingSpots[i]->write(file);
				}
			}
		}
		file.close();
	}
	int Parking::run()
	{
		int value = 1;
		if (!isEmpty()) {
			bool execution = true;
			do {
				parkingStatus();
				switch (parkingMenu.run()) {
				case 1:
					parkVehicle();
					break;
				case 2:
					returnVehicle();
					break;
				case 3:
					listParkedVehicles();
					break;
				case 4:
					if (closeParking())
						execution = false;
					break;
				case 5:
					if (exitParkingApp())
						execution = false;
					cout << "Exiting program!" << endl;
					break;
				}
			} while (execution);
			value = 0;
		}
		return value;
	}
}