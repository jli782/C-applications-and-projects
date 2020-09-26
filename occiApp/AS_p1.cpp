/*
Name: Jeffrey Li
Project MileStone 1
Initial Commit/Implementation
July 16, 2020
Part 2 Commit/Implementation
July 18, 2020
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <occi.h>
#include <string>
#include <iomanip>

//#define _TEST_

using oracle::occi::Environment;
using oracle::occi::Connection;

using namespace oracle::occi;
using namespace std;

//helper function prototypes
int menu(Connection* conn);
int getIntInput(int min, int max);
void clear();
bool exitApp();
bool isYesNo(const char c);
bool validString(const char* s, int max);
int getEmpNoInput();

struct Employee
{
	int employeeNumber;
	char lastName[50];
	char firstName[50];
	char email[100];
	char phone[50];
	char extension[10];
	char reportsTo[100];
	char jobTitle[50];
	char city[50];
	Employee()
	{
		employeeNumber = 0;
		lastName[0] = '\0';
		firstName[0] = '\0';
		email[0] = '\0';
		phone[0] = '\0';
		extension[0] = '\0';
		reportsTo[0] = '\0';
		jobTitle[0] = '\0';
		city[0] = '\0';
	}
	Employee(int employeeNo, const char* lname, const char* fname, const char* _email, const char* ext, const char* _jobtitle, const char* _city, const char* _phone, const char* _reportsTo = "102")
	{
		bool valid = employeeNo > 0 && validString(lname, 49) && validString(fname, 49) && validString(_email, 99) && validString(_phone, 49) && validString(ext, 9) && validString(_reportsTo, 99) && validString(_jobtitle, 49) && validString(_city, 49);
		employeeNumber = employeeNo;
		strcpy(lastName, lname);
		strcpy(firstName, fname);
		strcpy(email, _email);
		strcpy(phone, _phone);
		strcpy(extension, ext);
		strcpy(reportsTo, _reportsTo);
		strcpy(jobTitle, _jobtitle);
		strcpy(city, _city);
	}
	Employee& setUserInput()
	{
		int m_employeeNumber = 0;
		char m_lastName[50] = { 0 };
		char m_firstName[50] = { 0 };
		char m_email[100] = { 0 };
		char m_phone[50] = { 0 };
		char m_extension[10] = { 0 };
		char m_reportsTo[100] = { 0 };
		char m_jobTitle[50] = { 0 };
		char m_city[50] = { 0 };

		cout << "Please enter employee information.\n" << "Employee Number: ";
		m_employeeNumber = getIntInput(0, 10000);
		cout << "Last Name: ";
		cin.getline(m_lastName, 49);
		cout << "First Name: ";
		cin.getline(m_firstName, 49);
		cout << "Email: ";
		cin.getline(m_email, 99);
		cout << "extension: ";
		cin.getline(m_extension, 9);
		cout << "Job title: ";
		cin.getline(m_jobTitle, 49);
		cout << "City: ";
		cin.getline(m_city, 49);

		Employee temp(m_employeeNumber, m_lastName, m_firstName, m_email, m_extension, m_jobTitle, m_city, m_phone, m_reportsTo);
		*this = temp;
		return *this;
	}
};

//menu functions
int findEmployee(Connection* conn, int employeeNumber, Employee* emp);
void displayEmployee(Connection* conn, Employee emp);
void displayAllEmployees(Connection* conn);
void insertEmployee(Connection* conn, Employee emp);
void updateEmployee(Connection* conn, int employeeNumber);
void deleteEmployee(Connection* conn, int employeeNumber);

int main(void)
{
	Environment* env = nullptr;
	Connection* conn = nullptr;
	Statement* stmt = nullptr;
	ResultSet* rs = nullptr;

	int num;
	string str;
	string user = "dbs211_202d14";
	string pass = "14465175";
	string constr = "myoracle12c.senecacollege.ca:1521/oracle12c";

	try {

		env = Environment::createEnvironment(Environment::DEFAULT);
		conn = env->createConnection(user, pass, constr);
		std::cout << "Connection is successful!" << endl;
		menu(conn);

		//conn->terminateStatement(stmt);		//terminate statement
		env->terminateConnection(conn);		//terminate connection
		Environment::terminateEnvironment(env); //terminate environment

	}
	catch (SQLException& sqlExcp) {		//exception/error handling
		cout << "error";
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}

	return 0;
}

int menu(Connection* conn)
{
	int num = -1;
	bool execution = true;
	do {
		Employee emp;
		cout << "********************* HR Menu *********************" << endl << "1) Find Employee" << endl << "2) Employees Report" << endl << "3) Add Employee" << endl << "4) Update Employee" << endl << "5) Remove Employee" << endl << "6) Exit" << endl << "> ";
		switch (getIntInput(0, 6)) {
		case 1:
#ifdef _TEST_
			cout << "in 1) Find Employee" << endl;
#endif // DEBUG
			displayEmployee(conn, emp);
			break;
		case 2:
#ifdef _TEST_
			cout << "in 2) Employees Report" << endl;
#endif // DEBUG
			displayAllEmployees(conn);
			break;
		case 3:
#ifdef _TEST_
			cout << "in 3) Add Employee" << endl;
#endif // DEBUG
			emp.setUserInput();
			insertEmployee(conn, emp);
			break;
		case 4:
#ifdef _TEST_
			cout << "in 4) Update Employee" << endl;
#endif // DEBUG
			updateEmployee(conn, getEmpNoInput());
			break;
		case 5:
#ifdef _TEST_
			cout << "in 5) Remove Employee" << endl;
#endif // _TEST_
			deleteEmployee(conn, getEmpNoInput());
			break;
		case 6:
#ifdef _TEST_
			cout << "in 6) Exit" << endl;
#endif // _TEST_
			if (exitApp())
				execution = false;
			cout << "Exiting program!" << endl;
			break;
		default:
			break;
		}
	} while (execution);
	return num;
}
int findEmployee(Connection* conn, int employeeNumber, Employee* emp)
{
	int result = 0;
	//Statement* stmt = nullptr;
	//ResultSet* rs = nullptr;
	////return 1 if employee exists else 0 if employee dne
	Statement* stmt = conn->createStatement("SELECT e.employeenumber, e.lastname, e.firstname, e.email, phone, e.extension, m.firstname || ' ' || m.lastname AS reportsto, e.jobtitle, city FROM employees e LEFT OUTER JOIN employees m ON e.reportsto = m.employeenumber JOIN offices o ON o.officecode = e.officecode WHERE e.employeenumber = :1");
	stmt->setInt(1, employeeNumber);
	ResultSet* rs = stmt->executeQuery();
	if (rs->next()) {
#ifdef _TEST_
		cout << "query successful!";
#endif // _TEST_

		result = 1;
		emp->employeeNumber = rs->getInt(1);
		strcpy(emp->lastName, (rs->getString(2)).c_str());
		strcpy(emp->firstName, (rs->getString(3)).c_str());
		strcpy(emp->email, (rs->getString(4)).c_str());
		strcpy(emp->phone, (rs->getString(5)).c_str());
		strcpy(emp->extension, (rs->getString(6)).c_str());
		strcpy(emp->reportsTo, (rs->getString(7)).c_str());
		strcpy(emp->jobTitle, (rs->getString(8)).c_str());
		strcpy(emp->city, (rs->getString(9)).c_str());
	}
	else {
#ifdef _TEST_
		cout << "query unsuccessful!";
#endif // _TEST_
		result = 0;
	}

	conn->terminateStatement(stmt);
	return result;
}
void displayEmployee(Connection* conn, Employee emp)
{
	cout << "Enter employee number: ";
	int userInput = getIntInput(0, 10000);
	//int userInput = -1;
	//cin >> userInput;
	if (findEmployee(conn, userInput, &emp) == 0) {
		cout << userInput << " does not exist." << endl;
	}
	else {
		cout << endl << "employeeNumber = " << emp.employeeNumber << endl;
		cout << "lastName = " << emp.lastName << endl;
		cout << "firstName = " << emp.firstName << endl;
		cout << "email = " << emp.email << endl;
		cout << "phone = " << emp.phone << endl;
		cout << "extension = " << emp.extension << endl;
		cout << "reportsTo = " << emp.reportsTo << endl;
		cout << "jobTitle = " << emp.jobTitle << endl;
		cout << "city = " << emp.city << endl << endl;
	}
}
void displayAllEmployees(Connection* conn)
{
	Statement* stmt = conn->createStatement();
	ResultSet* rs = stmt->executeQuery("SELECT e.employeenumber, e.firstname || ' ' || e.lastname AS employeename, e.email, phone, e.extension, m.firstname || ' ' || m.lastname AS manager FROM employees e LEFT OUTER JOIN employees m ON e.reportsto = m.employeenumber JOIN offices o ON o.officecode = e.officecode ORDER BY e.employeenumber");
	if (!rs->next()) {//no results exist
		cout << "There is no employees' information to be displayed." << endl;
	}
	else {//display results
		cout << "E\t" << "Employee Name\t\t" "Email 				\tPhone 		 Ext	 Manager\n------------------------------------------------------------------------------------------------------------------------\n";
		do {//setw(31)
			cout << rs->getInt(1) << '\t' << setw(17) << left << rs->getString(2) << '\t' << setw(35) << rs->getString(3) << '\t' << setw(16) << rs->getString(4) << " " << setw(8) << rs->getString(5) << rs->getString(6) << endl;
		} while (rs->next());
		cout << right;
	}
	conn->terminateStatement(stmt);
}
void insertEmployee(Connection* conn, Employee emp)
{
	//cout << "Enter employee number: ";
	//int userInput = getIntInput(0, 10000);

	if (findEmployee(conn, emp.employeeNumber, &emp) == 1) {
		cout << "An employee with the same employee number exists." << endl;
	}
	else {
		//insert employee info, assume officecode=1 and reportsto=102 by default
		Statement* stmt = conn->createStatement();
		stmt->setSQL("INSERT INTO employees (employeenumber, lastname, firstname, extension, email, officecode, reportsto, jobtitle) VALUES(:1,:2,:3,:4,:5,:6,:7,:8)");
		stmt->setInt(1, emp.employeeNumber);
		stmt->setString(2, emp.lastName);
		stmt->setString(3, emp.firstName);
		stmt->setString(4, emp.extension);
		stmt->setString(5, emp.email);
		stmt->setString(6, "1");
		int officeCode = 1002;
		stmt->setInt(7, officeCode);
		stmt->setString(8, emp.jobTitle);
		stmt->executeUpdate();
		cout << endl << "The new employee is added successfully." << endl;
		conn->terminateStatement(stmt);
	}
}
void updateEmployee(Connection* conn, int employeeNumber)
{
	//updates the phone extension for selected employee
	Employee emp;

	if (findEmployee(conn, employeeNumber, &emp) == 1) {
		//update employee info

		char userExt[10] = { 0 };
		cout << "Please enter new information\n";
		cout << "New Extension: ";
		cin.get(userExt, 9);
		cin.ignore(100, '\n');
		Statement* stmt = conn->createStatement();
		stmt->setSQL("UPDATE employees SET extension= :1 WHERE employeenumber= :2");
		stmt->setString(1, userExt);
		stmt->setInt(2, employeeNumber);
		stmt->executeUpdate();
		cout << "Employee " << employeeNumber << " has been updated extension to "<< userExt << endl;
		conn->terminateStatement(stmt);
	}
	else {
		//insert employee info, assume officecode=1 and reportsto=102 by default
		cout << "The employee " << employeeNumber << " does not exist." << endl;
	}
}
void deleteEmployee(Connection* conn, int employeeNumber)
{
	//deletes a row with the given employee number from table employees
	Employee emp;
	if (findEmployee(conn, employeeNumber, &emp) == 0) {
		cout << "The employee does not exist." << endl;
	}
	else {
		Statement* stmt = conn->createStatement();
		stmt->setSQL("DELETE FROM employees WHERE employeenumber= :1");
		stmt->setInt(1, employeeNumber);
		stmt->executeUpdate();
		cout << "The employee is deleted." << endl;
		conn->terminateStatement(stmt);
	}
}

//helper functions
int getIntInput(int min, int max)
{
	int userIntegerInput = 0, inputCount = 0, flag = 0;
	char NL = 'x';

	do {
		inputCount = scanf("%d%c", &userIntegerInput, &NL);
		if (inputCount == 0) {
			std::cout << "Invalid Integer, try again: ";
			clear();
		}
		else if (NL != '\n') {
			std::cout << "Invalid trailing characters, try again: ";
			clear();
		}
		else if (userIntegerInput <= min || userIntegerInput > max) {
			std::cout << "Invalid selection, try again: ";
		}
		else {
			flag = 1;
		}
	} while (flag == 0);
	return userIntegerInput;
}
void clear()
{
	while (getchar() != '\n');
}
bool exitApp()
{
	cout << "This will terminate the program!" << endl << "Are you sure? (Y)es/(N)o: ";
	char input[10] = { 0 };
	int valid = 0;
	while (input[1] != '\n' && valid == 0) {
		std::cin >> input;
		if (input[1] == '\0' && isYesNo(input[0])) {
			valid = 1;
		}
		if (input[1] != '\0') {
			clear();
			std::cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
		}
	}
	bool value = false;
	if (toupper(input[0]) == 'Y') {
		value = true;
	}
	return value;
}
bool isYesNo(const char c)
{
	bool valid = false;
	if (c == 'Y' || c == 'y' || c == 'N' || c == 'n') {
		valid = true;
	}
	return valid;
}
bool validString(const char* s, int max)
{
	return s && strlen(s) > 0 && strlen(s) < max;
}
int getEmpNoInput()
{
	cout << "Enter employee number: ";
	int user = getIntInput(0, 10000);
	return user;
}
