#include <iostream>
#include <iomanip>
using namespace std;

#include "ItemToPurchase.h"

using namespace std;


int main() {
	int i;
	const int NUM_ITEMS = 2;
	string name;
	int price;
	int quantity;
	double total;
	ItemToPurchase item1;
	ItemToPurchase item2;

	for (i = 0; i < NUM_ITEMS; ++i) {
		cout << "Item " << i + 1 << endl;
		cout << "Enter the item name:" << endl;
		getline(cin, name);

		cout << "Enter the item price:" << endl;
		cin >> price;

		cout << "Enter the item quantity:" << endl;
		cin >> quantity;
		cout << endl;

		if (i == 0) {
			item1.SetName(name);
			item1.SetPrice(price);
			item1.SetQuantity(quantity);
		}

		else if (i == 1) {
			item2.SetName(name);
			item2.SetPrice(price);
			item2.SetQuantity(quantity);
		}

		cin.ignore();
	}

	total = (item1.GetPrice() * item1.GetQuantity()) + 
		(item2.GetPrice() * item2.GetQuantity());

	cout << "TOTAL COST" << endl;   
	item1.Print();
	item2.Print();
	cout << endl;
	cout << "Total: $" << total << endl;


	return 0;
}
