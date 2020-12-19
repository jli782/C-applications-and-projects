/************************
--Student1 Name : Jeffrey Li Student1 ID : 160203196
--Student2 Name : Heebin Lee Student2 ID : 130464191
--Student3 Name : Jared Lecesne Student3 ID : 166268185
--Date : November 25, 2020
--Purpose : Assignment 2 - DBS311
-- * ***********************/

#include <iostream>
#include <string>
#include <iomanip>
#include <occi.h>


using namespace oracle::occi;
using namespace std;

/***function prototypes***/
int mainMenu();
int customerLogin(Connection* conn, int customerId);
//TO DO ...
int addToCart(Connection* conn, struct ShoppingCart cart[]);
double findProduct(Connection* conn, int product_id);
void displayProducts(struct ShoppingCart cart[], int productCount);
int checkout(Connection* conn, struct ShoppingCart cart[], int customerId, int
	productCount);

/***helper functions***/
int getUserIntInput();
int YesorNo();

/***data structure***/
struct ShoppingCart
{
	int product_id;
	double price;
	int quantity;
};

int main(void)
{

	/* OCCI Variables */
	Environment* env = nullptr;
	Connection* conn = nullptr;
	/*Statement* stmt = nullptr;*///not required, should be create locally in each function
	/*ResultSet* rs = nullptr;*/

	/* Used Variables */
	string str;
	string user = "dbs311_203c22";
	string pass = "85450682";
	string constr = "myoracle12c.senecacollege.ca:1521/oracle12c";

	ShoppingCart cart[5]{ 0 }; //declare an object of pointer to shoopingCart struct
	try {

		env = Environment::createEnvironment(Environment::DEFAULT);
		conn = env->createConnection(user, pass, constr);
		// create environement and Open the connction 

		cout << "Connection is successful!" << endl;

		while (mainMenu()) {
			int custID = -1;
			cout << "Enter the customer ID: ";
			custID = getUserIntInput();

			if (customerLogin(conn, custID)) {
				int size = addToCart(conn, cart);
				displayProducts(cart, size);
				int check = checkout(conn, cart, custID, size);
				if (check)
					cout << "The order is successfully completed." << endl;
				else
					cout << "The order is cancelled." << endl;
			}
			else {
				cout << "The customer does not exist." << endl;
			}
		}
		cout<<"Good bye!..."<<endl;
		env->terminateConnection(conn);
		Environment::terminateEnvironment(env);
	}
	catch (const std::invalid_argument& ia) {
		cout << "error failed to convert from string to int.\n";
	}
	catch (SQLException& sqlExcp) {
		cout << "error";
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}

	return 0;
}

/*functions definitions*/
int mainMenu()
{
	int val = -99, flag = 1;
	string c="";
	cout << "******************** Main Menu ********************" << endl << "1)" << setw(11) << "Login" << endl << "0)" << setw(10) << "Exit" << endl << "Enter an option (0-1): ";
	while (flag == 1) {
		getline(cin, c);
		if (c[0] == '1' && c.length() == 1) {
			flag = 0;
			val = 1;
		}
		else if (c[0] == '0' && c.length() == 1) {
			flag = 0;
			val = 0;
		}
		else {
			cout << "******************** Main Menu ********************" << endl << "1)" << setw(11) << "Login" << endl << "0)" << setw(10) << "Exit" << endl << "You entered a wrong value. Enter an option (0-1): ";
			//cin.clear();
		}
	}
	


	return val;
}
int customerLogin(Connection* conn, int customerId)
{
	int val = 0;
	//cout << "customerLogin() : " << customerId << endl;

	Statement* stmt = conn->createStatement();
	stmt->setSQL("BEGIN find_customer(:1, :2); END;");
	stmt->setInt(1, customerId);
	stmt->registerOutParam(2, Type::OCCIINT, sizeof(val));
	stmt->executeUpdate();
	val = stmt->getInt(2);
	conn->terminateStatement(stmt);
	return val;
}
int addToCart(Connection* conn, struct ShoppingCart cart[])
{
	int val = -1; // return value
	int count = 0; // count up to 5 items for ordering
	int checkout = -1; // 0 for checkout

	cout << "-------------- Add Products to Cart --------------" << endl;

	for (count = 0; count < 5; count++)
	{
		cout << "Enter the product ID: ";
		cart[count].product_id = getUserIntInput();
		cart[count].price = findProduct(conn, cart[count].product_id);
		if (cart[count].price != 0)
		{
			cout << "Product Price: " << cart[count].price << endl;
			cout << "Enter the product Quantity: ";
			cart[count].quantity = getUserIntInput();
			checkout = -1;
			while (checkout == -1)
			{
				cout << "Enter 1 to add more products or 0 to checkout: ";
				checkout = getUserIntInput();
				if (checkout == 0)
				{
					val = count + 1;
					count = 5;
				}
				else if (checkout != 1)
					checkout = -1;
			}
		}
		else
		{
			cout << "The product does not exists. Try again..." << endl;
			count--;
		}

	}
	return val;
}

double findProduct(Connection* conn, int product_id)
{
	double val = 0.0;

	Statement* stmt = conn->createStatement("BEGIN find_product(:1, :2); END;");
	stmt->setInt(1, product_id);
	stmt->registerOutParam(2, Type::OCCIDOUBLE, sizeof(val));
	stmt->executeUpdate();
	val = stmt->getDouble(2);
	conn->terminateStatement(stmt);

	return val;
}

void displayProducts(struct ShoppingCart cart[], int productCount)
{
	double total = 0.0;

	cout << "------- Ordered Products ---------" << endl;
	for (int i = 0; i < productCount; i++)
	{
		cout << "---Item " << i + 1 << endl;
		cout << "Product ID: " << cart[i].product_id << endl;
		cout << "Price: " << cart[i].price << endl;
		cout << "Quantity: " << cart[i].quantity << endl;
		total += (cart[i].price * cart[i].quantity);
	}
	cout << "----------------------------------" << endl;
	cout << "Total: " << total << endl;
}


int checkout(Connection* conn, struct ShoppingCart cart[], int customerId, int productCount)
{
	int flag = -1;
	while (flag == -1)
	{
		cout << "Would you like to checkout? (Y/y or N/n) ";
		flag = YesorNo();
		if (flag == -1) {
			cout << "Wrong input. Try again..." << endl;
		}
		else {
			if (flag == 0) {
				//cout << "The order is canceled." << endl;
				break;
			}
			else {
				int order_id = 0;

				Statement* stmt = conn->createStatement("BEGIN add_order(:1, :2); END;");
				//stmt->setAutoCommit(TRUE);
				stmt->setInt(1, customerId);
				stmt->registerOutParam(2, Type::OCCIINT, sizeof(order_id));
				stmt->executeUpdate();
				
				
				order_id = stmt->getInt(2);
				conn->terminateStatement(stmt);

				Statement* stmt2 = conn->createStatement("BEGIN add_order_item(:1, :2, :3, :4, :5); END;");
				//stmt2->setAutoCommit(TRUE);

				for (int i = 0; i < productCount; i++) {
					stmt2->setInt(1, order_id);
					stmt2->setInt(2, i+1);
					stmt2->setInt(3, cart[i].product_id);
					stmt2->setInt(4, cart[i].quantity);
					stmt2->setDouble(5, cart[i].price);
					stmt2->executeUpdate();
				}
				//conn->commit();
				conn->terminateStatement(stmt2);
				//cout << "The order is successfully completed." << endl;
				break;
			}
		}
	}

	return flag;
}

/*helper definitions*/
int getUserIntInput()
{
	int val = -1;
	string s;

	getline(cin, s);
	val = stoi(s);
	return val;
}
int YesorNo()
{
	string yn = "";
	int val = -1;
	getline(cin, yn);
	if (yn == "Y" || yn == "y")
		val = 1;
	else if (yn == "N" || yn == "n")
		val = 0;
	else
		val = -1;

	return val;
}


