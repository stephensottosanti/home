// Shopping Cart

#include <iostream>
#include <iomanip>
using namespace std;

#include "ShoppingCart.h"

using namespace std;

char PrintMenu(ShoppingCart& theCart){
   char menuOp = ' ';
   string name;
   string descr;
   int price = 0;
   int quantity = 0;
   
   cout << "MENU" << endl;
   cout << "a - Add item to cart" << endl;
   cout << "d - Remove item from cart" << endl;
   cout << "c - Change item quantity" << endl;
   cout << "i - Output items' descriptions" << endl;
   cout << "o - Output shopping cart" << endl;
   cout << "q - Quit" << endl << endl;
   
   while (menuOp != 'a' && menuOp != 'd' && menuOp != 'c' &&
         menuOp != 'i' && menuOp != 'o' && menuOp != 'q') {
      cout << "Choose an option:" << endl;
      cin >> menuOp;
   }
   
   switch(menuOp) {
      case 'a':
      {
         cin.ignore();
         
         cout << "ADD ITEM TO CART" << endl;
         cout << "Enter the item name:" << endl;
         getline(cin, name);
         
         cout << "Enter the item description:" << endl;
         getline(cin, descr);
      
         cout << "Enter the item price:" << endl;
         cin >> price;
      
         cout << "Enter the item quantity:" << endl;
         cin >> quantity;
         
         ItemToPurchase newItem(name, descr, price, quantity);
         theCart.AddItem(newItem);
         
         menuOp = ' ';
         cout << endl;
      }
      break;
      
      case 'd':
         cin.ignore();
         
         cout << "REMOVE ITEM FROM CART" << endl;
         cout << "Enter name of item to remove:" << endl;
         getline(cin, name);
         
         theCart.RemoveItem(name);
         
         menuOp = ' ';
         cout << endl;
      break;
      
      case 'c':
      {
         cin.ignore();
         
         cout << "CHANGE ITEM QUANTITY" << endl;
         cout << "Enter the item name:" << endl;
         getline(cin, name);
         
         cout << "Enter the new quantity:" << endl;
         cin >> quantity;
         
         ItemToPurchase item;
         item.SetName(name);
         item.SetQuantity(quantity);
         
         theCart.ModifyItem(item);
         
         menuOp = ' ';
         cout << endl;
      }
      break;
      
      case 'i':
         cout << "OUTPUT ITEMS' DESCRIPTIONS" << endl;
         theCart.PrintDescriptions();
         
         menuOp = ' ';
         cout << endl;
      break;
      
      case 'o':
         cout << "OUTPUT SHOPPING CART" << endl; 
         theCart.PrintTotal();
         
         menuOp = ' ';
         cout << endl;
      break;
   }
   
   return menuOp;
   
}

Main Done



Items cpp
#include <iostream>
using namespace std;

#include "ItemToPurchase.h"

ItemToPurchase::ItemToPurchase() {
   itemName = "none";
   itemPrice = 0;
   itemQuantity = 0;
   itemDescr = "none";
   return;
}
/*void ItemToPurchase::SetNewItem(string name, string descr, int price, int quantity){
   itemName = name;
   itemDescr = descr;
   itemPrice = price;
   itemQuantity = quantity;
}
*/
void ItemToPurchase::SetDescr(string descr) {
   itemDescr = descr;
   return
}
void ItemToPurchase::SetName(string name) {
   itemName = name;
   
   return;
}

void ItemToPurchase::SetPrice(int price) {
   itemPrice = price;
   
   return;
}

void ItemToPurchase::SetQuantity(int quantity) {
   itemQuantity = quantity;
   
   return;
}

string ItemToPurchase::GetName() const {
   return itemName;
}

int ItemToPurchase::GetPrice() const {
   return itemPrice;
}

int ItemToPurchase::GetQuantity() const {
   return itemQuantity;
}

void ItemToPurchase::Print() {
   cout << itemName << " " << itemQuantity << " @ $"
        << itemPrice << " = $" << itemPrice * itemQuantity << endl;
}
Items ended

Items h

#ifndef ITEM_TO_PURCHASE_H
#define ITEM_TO_PURCHASE_H


#include <string>
using namespace std;

class ItemToPurchase {
   
   public:
      ItemToPurchase();      
      void SetName(string name);
      void SetPrice(int price);
      void SetQuantity(int quantity);
      void SetDescription(string discr);
      void SetNewItem(string name, string descr, int price, int quantitiy);
      
      string GetName() const;
      int GetPrice() const;
      int GetQuantity() const;
      
      void Print();
   
   private:
      string itemName;
      int itemPrice;
      int itemQuantity;
      string itemDescr;
};


#endif

Items ended

Shopping h
#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H
#include <iostream>

#include "ItemToPurchase.h"
#include <vector>
#include <string>
using namespace std;

class ShoppingCart {
   string customerName;
   string currentDate;
   vector<ItemToPurchase> theCart;
   
public:
   ShoppingCart()
   {
      this->customerName = "none";
      this->currentDate = "February 1, 2016";
   }
   ShoppingCart(string customerName, string customerDate)
   {
      this->customerName = customerName;
      this->currentDate = currentDate;
   }
   
   string GetCustomerName();
   string GetDate();
   
   void AddItem(ItemToPurchase newItem);
   void RemoveItem(string name);
   void ModifyItem(item);
   
   int GetNumItemsInCart();
   int GetCostOfCart();
   
   void PrintTotal();
   void PrintDescriptions();

private:
   void PrintHeader();
};
   
#endif

End shopping h


Shopping cpp

#include <iostream>
using namespace std;

#include <stdbool.h>
#include "ShoppingCart.h"

string ShoppingCart::GetCustomerName()
{
   return this->customerName;
}
string ShoppingCart::GetDate()
{
   return this->currentDate;
}
void ShoppingCart::AddItem(ItemToPurchase newItem)
{
   this->theCart.push_back(item);
}
void ShoppingCart::RemoveItem(string itemName)
{
   bool found = false;
   for (int i = 0; i < this->cartItems.size(); i++)
   {
      if this->theCart.at(i).name ==itemName)
      {
         found = true;
         this->theCart.erase(cartItems.begin() + 1);
      }
   }
   if(!found)
   {
      cout<<endl<<"Item not found in cart. Nothing removed."<<endl <<endl;
   }
}
void ShoppingCart::ModifyItem(item);
{
   bool found = false;
   for(int i = 0; i < this->theCart.size(); i++)
   {
      if (this->theCart.at(i).name == item.name)
      {
         found = true;
         this->theCart.at(i).quantity = item.quantity;
      }
   }
   if(!found)
   {
      cout<< endl << "Item not found in cart. Nothing modified." << endl;
   }
}
int ShoppingCart::GetNumItemsInCart()
{
   return this->theCart.size();
}
int ShoppingCart::GetCostofCart()
{
   int totalCost = 0;
   if(this->theCart.size() == 0)
   {
      return 0:
   }
   for(int i = 0; i < this->cartItems.size(); i++)
   {
      totalCost += this->theCart.at(i).price * this->cartItems.at(i).quantity;
   }
   return totalCost;
   
}
void ShoppingCart::PrintHeader()
{
   cout<< this->customerName << "'s Shopping Cart" <<this->currentDate <<endl;
}
void ShoppingCart::PrintTotal()
{
   if(this->theCart.size() == 0) 
   {
      cout <<"SHOPPING CART IS EMPTY." << endl;
   }
   else
   {
      this->PrintHeader();
      cout<< "Number of items: " << this->theCart.size() << endl << endl;
   }
}

void ShoppingCart::PrintDescriptions()
{
   this->PrintHeader();
   cout<< endl;
   cout<<"Item Descriptions: " << endl;
   for(int i == 0; i < this->theCart.size(); i++)
   {
      this->theCart.at(i).PrintDescription();
      cout<<endl;
   }
}
      