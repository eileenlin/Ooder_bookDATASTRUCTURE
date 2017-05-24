// ConsoleApplication3.cpp : Defines the entry point for the console application.
//


#include<string>
#include<cmath>
#include<algorithm>
#include<fstream>
#include <vector>
#include "OrderBook.h"





using namespace std;

int main()
{
	OrderBook myorder;  //creat  an order book;
	string action;
	ifstream myinput;
	myinput.open("inputfile.txt");
	
	int order_id;
	char side;
	double price;
	int size;
	int level;
	

	while (myinput)
	{
		myinput >> action;

		if (action == "add")
		{   //myorder.add();


			myinput >> order_id;
			myinput >> side;
			myinput >> price;
			myinput >> size;
			myorder.add(order_id, side, price, size);
			//cout << "add one entry!" << endl;

		}


		else if (action == "modify")
		{
			myinput >> order_id;

			myinput >> size;
			
			myorder.modify(order_id, size);
			//cout << "modify one" << endl;
			

		}
		else if (action == "remove")
		{
			myinput >> order_id;
			myorder.remove(order_id);
			//cout << "remove one!" << endl;
		}
		else if (action == "get")
		{ 
			myinput >> action;
			if (action == "price")
			{
				
				myinput >> side;
				myinput >> level;
			cout <<	myorder.get_price(side, level)<< endl;
			}
			else if (action == "size")
			{
				
				myinput >> side;
				myinput >> level;
				cout <<myorder.get_size(side, level)<< endl;

			}


		}
		//else (action.substr(0, 2) == "//")
		//{
		//	continue;
		//}




	}
	myinput.close();


	return 0;
}



	