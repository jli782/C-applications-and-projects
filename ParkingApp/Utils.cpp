/* Citation and Sources...
Final Project Milestone 6
Module: Utils
Filename: Utils.cpp
Version 2.0
Author	Jeffrey Li
Revision History
-----------------------------------------------------------
Date      Reason
2020/7/14 Utils, global functions declared (preliminary release)
2020/7/28 implemented global scoped user input validations
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/
#include <cstring>
#include <iostream>
namespace sdds
{
	void clear(void)
	{
		while (getchar() != '\n');
	}
	bool checkValidString(const char* string)
	{
		return string && std::strlen(string) != 0;
	}
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
	bool isYesNo(const char c)
	{
		bool valid = false;
		if (c == 'Y' || c == 'y' || c == 'N' || c == 'n') {
			valid = true;
		}
		return valid;
	}
	int yesNoPrompt()
	{
		char input[10] = { 0 };
		int valid = 0;
		while (input[1] != '\n' && valid == 0) {
			std::cin >> input;
			if (input[1] == '\0' && isYesNo(input[0])) {
				valid = 1;
				
			}
			if (input[1] != '\0') {
				
				std::cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
			}
			std::cin.ignore(1000, '\n');
		}
		int value = 0;
		if (toupper(input[0]) == 'Y') {
			value = 1;
		}
		return value;
	}
	void uppercase(char* str)
	{
		int i = 0;
		while (str[i] != '\0') {
			str[i] = toupper(str[i]);
			i++;
		}
	}
	void inputLicense(char* s, int n)
	{
		std::cout << "Enter Licence Plate Number: ";
		std::cin.get(s, n);

		while (strlen(s) > 8 || s[0] == '\0') {
			std::cout << "Invalid Licence Plate, try again: ";
			std::cin.ignore(1000, '\n');
			if (s[0] == '\0') {
				s[0] = '!';
				std::cin.clear();
				std::cin.ignore(1000, '\n');
			}
			std::cin.get(s, n);
		}
		std::cin.ignore(1000, '\n');
		std::cin.clear();
	}
	void inputMM(char* s, int n)
	{
		std::cout << "Enter Make and Model: ";
		std::cin.get(s, n);

		while (strlen(s) > 60 || strlen(s) < 2 || s[0] == '\0') {
			std::cout << "Invalid Make and model, try again: ";
			std::cin.ignore(1000, '\n');
			if (s[0] == '\0') {
				s[0] = '!';
				std::cin.clear();
				std::cin.ignore(1000, '\n');
			}
			std::cin.get(s, n);
		}
		std::cin.ignore(1000, '\n');
		std::cin.clear();
	}
}

