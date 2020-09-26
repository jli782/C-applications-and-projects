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
2020/7/28 added user input validations
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/
#ifndef __UTILS__
#define __UTILS__
namespace sdds
{
	void clear(void);
	bool checkValidString(const char* string);
	int getIntInput(int min, int max);
	bool isYesNo(const char c);
	int yesNoPrompt();
	void uppercase(char* str);
	void inputLicense(char* s, int n);
	void inputMM(char* s, int n);
}
#endif