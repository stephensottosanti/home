
#include<string>
#include <iostream>
using namespace std;

//Class name
class ItemToPurchase
{
	//Access specifier
	public:

		//Constructor
		ItemToPurchase(string, int, int);

		//Default Constructor 
		ItemToPurchase();

		//Function Declerations.
		void SetName(string);
		void SetPrice(int);
		void SetQuantity(int);

		string GetName();
		int GetPrice();
		int GetQuantity();      	
		
		void Print();
		 

	//Access specifier 
	private:
		//Variable declerations.
		string itemName;
		int itemPrice;
		int itemQuantity;
		
};
