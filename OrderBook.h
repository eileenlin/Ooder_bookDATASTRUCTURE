#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;


struct Order_entry {
	int order_id;
	int order_size;
	char side;
	double price;

};

class OrderBook {
public:
    void  add(int order_id, char side, double price, int size);
    void modify(int order_id, int new_size);
	void remove(int order_id);
    double get_price(char side, int level);
    int get_size(char side, int level);
	virtual ~OrderBook();

private: 

	vector <Order_entry> full_book;

	vector<int> Bsize;
	vector<double> Bprice;
	vector<int> Ssize;
	vector<double> Sprice;
   int EntryNum;

};



