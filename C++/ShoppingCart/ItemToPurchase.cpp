#include <iostream>
#include <string>
#include "ItemToPurchase.h"
using namespace std;

ItemToPurchase::ItemToPurchase()
{
	itemName = "none";
	itemPrice = 0;
	itemQuantity = 0;
}

void ItemToPurchase::SetName(string name)
{
	itemName = name;
}

void ItemToPurchase::SetPrice(int itemPrice)
{
	this->itemPrice = itemPrice;
}

void ItemToPurchase::SetQuantity(int itemQuantity)
{
	this->itemQuantity = itemQuantity;
}

string ItemToPurchase::GetName()
{
	return itemName;
}

int ItemToPurchase::GetPrice()
{
	return itemPrice;
}

int ItemToPurchase::GetQuantity()
{
	return itemQuantity;

}
void ItemToPurchase::Print() {
     cout << itemName <<" "<< itemQuantity << " @ $" << itemPrice << " = $" << (itemPrice * itemQuantity) << endl;;
}
