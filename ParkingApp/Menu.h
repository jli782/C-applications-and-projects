/* Citation and Sources...
Final Project Milestone 6 
Module: Menu
Filename: Menu.h
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
#ifndef __MENU__
#define __MENU__

namespace sdds
{
	const int MAX_NO_OF_ITEMS = 10;
	class Menu;
	class MenuItem
	{
		char* m_itemString;
		MenuItem();
		MenuItem(const char*);
		virtual ~MenuItem();
		void display() const;
		void dynamicAlloMenuItem(const char* original);
		MenuItem(const MenuItem& src) = delete;
		MenuItem& operator=(const MenuItem& src) = delete;
		friend class Menu;
	};
	class Menu
	{
		char* m_titleOfMenu;
		int m_indentation;
		int m_currentNoMenuItems;
		MenuItem* m_menuItems[MAX_NO_OF_ITEMS];
		void indent() const;
		void dynamicAlloTitle(const char* original);
		void displayTitle() const;
		void init(const Menu& src);
		void clearMenuItems();
		void makeNullMenuItems(const char* str);
	public:
		Menu();
		Menu(const char*, int indent = 0);
		Menu(const Menu& src);
		~Menu();
		Menu& operator=(const Menu& src);
		operator bool() const;
		bool isEmpty() const;
		void display() const;
		Menu& operator=(const char*);
		void add(const char*);
		Menu& operator<<(const char*);
		int run() const;
		operator int() const;
	};
}
#endif