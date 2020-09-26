/* Citation and Sources...
Final Project Milestone 2-6
Module: Menu
Filename: Menu.cpp
Version 1.0
Author	Jeffrey Li
Revision History
-----------------------------------------------------------
Date      Reason
2020/7/8  Preliminary release
2020/7/10  Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code 
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/
#include <iostream>
#include <cstring>
#include "Menu.h"
#include "Utils.h"
using namespace std;

namespace sdds
{
	//MenuItem member functions
	MenuItem::MenuItem() :m_itemString(nullptr)
	{
	}
	MenuItem::MenuItem(const char* string) /*: m_itemString(nullptr)*/
	{
		if (checkValidString(string)) {
			dynamicAlloMenuItem(string);
		}
		else {
			m_itemString = nullptr;
		}
	}
	MenuItem::~MenuItem()
	{
		delete[] m_itemString;
	}
	void MenuItem::display() const
	{
		if (m_itemString) {
			cout << m_itemString << endl;
		}
	}
	void MenuItem::dynamicAlloMenuItem(const char* original)
	{
		if (original == nullptr) {

			m_itemString = nullptr;
		}
		else {
			delete[] m_itemString;
			m_itemString = new char[strlen(original) + 1];
			strcpy(m_itemString, original);
		}
	}
	void Menu::dynamicAlloTitle(const char* original)
	{
		if (original == nullptr) {
			m_titleOfMenu = nullptr;
		}
		else {
			m_titleOfMenu = new char[strlen(original) + 1];
			strcpy(m_titleOfMenu, original);
		}
	}

	Menu::Menu() :m_titleOfMenu(nullptr), m_indentation(0), m_currentNoMenuItems(0)
	{
		makeNullMenuItems(nullptr);
	}
	void Menu::indent() const
	{
		for (int i = 0; i < m_indentation * 4; i++) {
			std::cout << " ";
		}
	};

	Menu::Menu(const char* str, int indent)
	{
		if (checkValidString(str)) {
			dynamicAlloTitle(str);
			m_indentation = indent < 0 ? 0 : indent;
			m_currentNoMenuItems = 0;
			makeNullMenuItems(nullptr);
		}
		else {
			Menu temp;
			*this = temp;
		}
	}
	void Menu::makeNullMenuItems(const char* str)
	{
		for (int i = 0; i < MAX_NO_OF_ITEMS; i++) {
			m_menuItems[i] = new MenuItem;
			m_menuItems[i]->dynamicAlloMenuItem(str);
		}
	}
	void Menu::init(const Menu& src)
	{
		m_indentation = src.m_indentation;
		m_currentNoMenuItems = src.m_currentNoMenuItems;
		if (checkValidString(src.m_titleOfMenu)) {
			dynamicAlloTitle(src.m_titleOfMenu);
		}
		else {
			m_titleOfMenu = nullptr;
		}
		if (src.m_menuItems && m_currentNoMenuItems > 0) {
			for (int i = 0; i < MAX_NO_OF_ITEMS; i++) {
				m_menuItems[i] = new MenuItem;
				m_menuItems[i]->dynamicAlloMenuItem(src.m_menuItems[i]->m_itemString);
			}
		}
		else {
			for (int i = 0; i < MAX_NO_OF_ITEMS; i++) {
				m_menuItems[i] = nullptr;
			}
		}
	}
	Menu::Menu(const Menu& src)
	{
		init(src);
	}
	Menu& Menu::operator=(const Menu& src)
	{
		if (this != &src) {

			delete[] m_titleOfMenu;
			clearMenuItems();
			init(src);
		}
		return *this;
	}
	Menu::~Menu()
	{
		clearMenuItems();
		delete[] m_titleOfMenu;
	}
	Menu::operator bool() const
	{
		return m_menuItems[0] != nullptr;
	}
	bool Menu::isEmpty() const
	{
		return m_menuItems[0] == nullptr;
	}
	void Menu::displayTitle() const
	{
		indent();
		cout << m_titleOfMenu << endl;
	}
	void Menu::display() const
	{
		if (m_titleOfMenu == nullptr) {
			cout << "Invalid Menu!" << endl;
		}
		else if (isEmpty()) {
			if (m_titleOfMenu != nullptr) {
				displayTitle();
			}
			cout << "No Items to display!" << endl;
		}
		else {
			displayTitle();
			for (int i = 0; i < m_currentNoMenuItems; i++) {
				indent();
				cout << i + 1 << "- ";
				m_menuItems[i]->display();
			}
			indent();
			cout << "> ";
		}
	}
	void Menu::add(const char* str)
	{
		if (m_currentNoMenuItems < MAX_NO_OF_ITEMS && !isEmpty()) {
			if (checkValidString(str)) {
				delete m_menuItems[m_currentNoMenuItems++];
				m_menuItems[m_currentNoMenuItems - 1] = new MenuItem;
				m_menuItems[m_currentNoMenuItems - 1]->dynamicAlloMenuItem(str);
			}
			else {
				Menu temp;
				*this = temp;
			}
		}

	}
	Menu& Menu::operator<<(const char* str)
	{
		add(str);
		return *this;
	}
	int Menu::run() const
	{
		int userIntegerInput = 0;
		display();
		if (!isEmpty()) userIntegerInput = getIntInput(0, m_currentNoMenuItems);

		return userIntegerInput;
	}
	Menu& Menu::operator=(const char* str)
	{
		if (checkValidString(str)) {
			delete[] m_titleOfMenu;
			dynamicAlloTitle(str);
		}
		else {
			delete[] m_titleOfMenu;
			clearMenuItems();
			Menu temp;
			*this = temp;
		}
		return *this;
	}
	Menu::operator int() const
	{
		return run();
	}
	void Menu::clearMenuItems()
	{
		for (int i = 0; i < MAX_NO_OF_ITEMS; i++) {
			if (m_menuItems[i]) {
				delete m_menuItems[i];
			}
		}
	}
}