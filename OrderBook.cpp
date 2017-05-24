#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>
#include "OrderBook.h"

using namespace std;

void OrderBook::add(int order_id, char side, double price, int size) {
	//initialize a new entry;
	Order_entry newone = {};
	newone.order_id = order_id;
	newone.side = side;
	newone.order_size = size;
	newone.price = price;

	//push it into the book
	full_book.push_back(newone);
	if (side == 'B') {
		Bsize.push_back(size);
		Bprice.push_back(price);
		

	}

	else if(side=='S') {
		Ssize.push_back(size);
		Sprice.push_back(price);
		

	}

}


void OrderBook::modify(int order_id, int new_size) {

	bool found = false;
	//find the entry where the order is located
	for (int  it = 0; it < full_book.size(); it++)
	{
		// if find the existing id, update the new size
		if (full_book[it].order_id == order_id)
		{
			found = true;

			if (full_book[it].side == 'B')
			{
				for (int j = 0; j < Bprice.size(); j++)
				{
					if (full_book[it].price == Bprice[j] && full_book[it].order_size == Bsize[j])
					{
						Bsize[j] = new_size;
						break;
					}
				}
			}
			else
			{
				for (int j = 0; j < Sprice.size(); j++)
				{
					if (full_book[it].price == Sprice[j] && full_book[it].order_size == Ssize[j])
					{
						Ssize[it] = new_size;
						break;
					}
				}
			}

			full_book[it].order_size = new_size;
		}
	}
	if (found==false)
	{
		cout << "No existing order id found in the orderbook !";
	}


}


void OrderBook::remove(int order_id) {


	bool found = false;
	int loca;

	//find the entry where the order is located
	for (int it = 0; it < full_book.size(); it++)
	{
		// if find the existing id, errase the vector
		if (full_book[it].order_id == order_id)
		{
			found = true;
			loca = it;

		}

	}
	if (found == true) {
		//cout << "begin remove" << endl;
		if (full_book[loca].side == 'B')
		{
			for (int j = 0; j < Bprice.size(); j++)
			{
				if (full_book[loca].price == Bprice[j] && full_book[loca].order_size == Bsize[j])
				{
					Bsize.erase(j + Bsize.begin());
					Bprice.erase(j + Bprice.begin());
					break;
				}
			}
		}
		else
		{

			for (int j = 0; j < Sprice.size(); j++)
			{
				if (full_book[loca].price == Sprice[j] && full_book[loca].order_size == Ssize[j])
				{
					Ssize.erase(j + Ssize.begin());
					Sprice.erase(j + Sprice.begin());
					break;
				}
			}

		}

		full_book.erase(full_book.begin() + loca);

	}


}

double OrderBook::get_price(char side, int level) {

	if ((side != 'B' && side != 'S' )|| level <= 0) return -1;
	
	vector<double> temp;
	
	if (side == 'B') {
		int num = Bprice.size();
		// if B, level means the highest price 
		temp = Bprice;
		sort(temp.begin(), temp.end());
		return temp[num-level]; //highest should be last indice
	}
	else if (side == 'S')
	{
		// return level th lowest price 

		temp = Sprice;
		sort(temp.begin(), temp.end());
		return temp[level-1];

	}

	return -1;
}

int OrderBook::get_size(char side, int level) {

	// need to keep track of index 
	if ((side != 'B' && side != 'S' )|| level <= 0) return -1;

	vector<double> temp;
	
	double curprice;
	int sumorder=0;
	if (side == 'B') {
		// if B, level means the highest price 
		int num = Bprice.size();
		temp = Bprice;
		sort(temp.begin(), temp.end());
		//need the index for the size;
		//cout << num << level << endl;
		curprice = temp[num - level];
		
		for (int i = 0; i < num; i++)
		{
			if (Bprice[i] == curprice)
				sumorder += Bsize[i];
		}
		return sumorder;

	}
	else if (side == 'S')
	{
		// return level th lowest price 
		int num = Sprice.size();
		//cout << num << endl;
		temp = Sprice;
		sort(temp.begin(), temp.end());

		curprice = temp[level-1];
		//cout << num << level << endl;
		//cout << curprice << endl;
		for (int i = 0; i < num; i++)
		{
			if (Sprice[i] == curprice)
				sumorder += Ssize[i];
		}
		return sumorder;

	}

	return -1;

}

OrderBook::~OrderBook()
{

	cout << " End of programing!" << endl;
}