#include <iostream>
#include <cstdlib>
using namespace std;
#include "RBTree.cpp"

void printErrors(string errors, int numOfErrors){
	if(numOfErrors < 5){
		cout << errors << " PASSED " << endl;
	}else if(numOfErrors < 100){
		cout << errors << " caused " << numOfErrors << " of errors Add+1" << endl;
		cout << errors << " caused " << numOfErrors << " of errors Add+1" << endl;
		cout << errors << " caused " << numOfErrors << " of errors Add+1" << endl;
	}else if (numOfErrors < 1000){
		cout << errors << " caused " << numOfErrors << " of errors Add+1" << endl;
		cout << errors << " caused " << numOfErrors << " of errors Add+1" << endl;
	}else if (numOfErrors < 10000){
		cout << errors << " caused " << numOfErrors << " of errors Add+1" << endl;
	}else{
		cout << errors << " caused " << numOfErrors << " of errors" << endl;
	}
}

// void test1();
// void test2();
// void test3();
// void test4();
// void test5();
void test6();
//void test7();
void test8();
void removeIndex(int removeIndex);

int main(){
	test8();
}

// void test1(){
// 	string K[14] = {"M","A","Q","R","F","E","L","V","S","T","W","X","Y","Z"};
// 	int V[14] = {10,9,8,7,6,5,4,3,2,1,11,12,13,14};
//
// 	RBTree<string,int> T1, T2(K,V,14);
//
// 	for(int i=0; i<14; i++) T1.insert(K[i],V[i]);
// 	// T1 and T2 should be identical trees
//
// 	T2.preorder();
// 	//Should output M E A F Q R
// 	cout << endl;
//
// 	T2.inorder();
// 	//Should output A E F M Q R
// 	cout << endl;
//
// 	T1.inorder();
// 	//Should output A E F M Q R
// 	cout << endl;
//
// 	T2.postorder();
// 	//Should output F A E R Q M
// 	cout << endl;
//
// 	cout << T2.remove("Z") << endl;
// 	//Should output 1
//
// 	cout << T2.remove("X") << endl;
// 	//Should output 1
//
// 	cout << T2.remove("C") << endl;
// 	//Should output 0
//
// 	T2.inorder();
// 	//Should output A E F M Q R
// 	cout << endl;
// }
//
//
// void test2(){
// 	string K[11] = {"A","B","C","D","E","F","H","I","J","K","L"};
// 	int V[11] = {10,9,8,7,6,5,4,3,2,1,0};
//
// 	RBTree<string,int> T1, T2(K,V,11);
// 	T2.postorder();
// 	cout << endl;
//
// 	for(int i=0; i<11; i++) T1.insert(K[i],V[i]);
// 	// T1 and T2 should be identical trees
//
// 	cout << T2.rank("A") << endl;
// 	cout << T2.rank("B") << endl;
//
// 	T1.insert("AF",11);
// 	T1.insert("AE",12);
// 	T1.insert("AD",13);
// 	cout << *(T1.search("AF")) << endl;
//
// 	cout << T1.rank("I") << endl;
//
// 	cout << T1.select(5) << endl;
//
// 	T1.preorder();
// 	cout << endl;
//
// 	T1.inorder();
// 	cout << endl;
//
// 	cout << T1.remove("HAHA") << endl;
//
// 	cout << T1.remove("AD") << endl;
//
// 	cout <<T1.rank("K") << endl;
//
// 	T1.inorder();
// 	cout << endl;
// 	cout << "Finished without failing" << endl << endl;
// }
//
// void test3(){
// 	string K[8] = {"M","H","Q","A","K","O","W","F"};
// 	int V[8] = {10,9,8,7,6,5,4,3};
//
// 	RBTree<string,int> T1, T2(K,V,8);
//
// 	for(int i=0; i<8; i++) T1.insert(K[i],V[i]);
// 	// T1 and T2 should be identical trees
//
// 	T2.preorder();
// 	//Should output M E A F Q R
// 	cout << endl;
//
// 	T2.inorder();
// 	//Should output A E F M Q R
// 	cout << endl;
//
// 	T1.inorder();
// 	//Should output A E F M Q R
// 	cout << endl;
//
// 	T2.postorder();
// 	//Should output F A E R Q M
// 	cout << endl;
//
// 	cout << T2.remove("H") << endl;
// 	//Should output 1
//
// 	cout << T2.remove("C") << endl;
// 	//Should output 0
//
// 	T2.inorder();
// 	//Should output A E F M Q R
// 	cout << endl;
//
// }
//
// void test4(){
// 	string K[12] = {"G","H","J","I","A","B","K","M","D","E","C","F"};
// 	int V[12] = {10,9,8,7,6,5,4,3,2,1,11,12};
//
// 	RBTree<string,int> T1, T2(K,V,12);
//
// 	for(int i=0; i<12; i++) T1.insert(K[i],V[i]);
// 	// T1 and T2 should be identical trees
//
// 	// T2.preorder();
// 	// //Should output M E A F Q R
// 	// cout << endl;
// 	//
// 	// T2.inorder();
// 	// //Should output A E F M Q R
// 	// cout << endl;
// 	//
// 	// T1.inorder();
// 	// //Should output A E F M Q R
// 	// cout << endl;
// 	//
// 	// T2.postorder();
// 	// //Should output F A E R Q M
// 	// cout << endl;
//
// 	// cout << T2.rank("A") << endl;
// 	// cout << T2.rank("B") << endl;
// 	// cout << T2.rank("M") << endl;
// 	// cout << T2.rank("K") << endl;
// 	//
// 	// cout << T2.select(1) << endl;
// 	// cout << T2.select(2) << endl;
// 	// cout << T2.select(3) << endl;
// 	// cout << T2.select(4) << endl;
// 	// cout << T2.select(5) << endl;
// 	// cout << T2.select(6) << endl;
// 	// cout << T2.select(7) << endl;
// 	// cout << T2.select(8) << endl;
// 	// cout << T2.select(9) << endl;
// 	// cout << T2.select(10) << endl;
// 	// cout << T2.select(11) << endl;
// 	// cout << T2.select(12) << endl;
//
//
// 	// cout << T2.remove("A") << endl;
// 	// //Should output 1
// 	//
// 	// T2.inorder();
// 	// //Should output A E F M Q R
// 	// cout << endl;
// 	//
// 	// cout << T2.rank("B") << endl;
// 	// //Should output 1
//
// }
//
// void test5(){
// 	string K[8] = {"M","Q","A","K","O","W","F","I"};
// 	int V[8] = {10,9,8,7,6,5,4,3};
//
// 	RBTree<string,int> T1, T2(K,V,8);
//
// 	for(int i=0; i<8; i++) T1.insert(K[i],V[i]);
// 	// T1 and T2 should be identical trees
//
// 	T2.preorder();
// 	//Should output M E A F Q R
// 	cout << endl;
//
// 	T2.inorder();
// 	//Should output A E F M Q R
// 	cout << endl;
//
// 	T1.inorder();
// 	//Should output A E F M Q R
// 	cout << endl;
//
// 	T2.postorder();
// 	//Should output F A E R Q M
// 	cout << endl;
//
// 	cout << T2.remove("A") << endl;
// 	//Should output 1
//
// 	T2.inorder();
// 	//Should output A E F M Q R
// 	cout << endl;
//
// }

void test6(){

	RBTree<int,int> X;
	for (int i=1000;i>=0;i--) X.insert(i,1000-i);
	for (int i=0;i<1000;i+=13) X.remove(i);

	// X.preorder();
  // cout << endl;
	//
	// X.postorder();
  // cout << endl;
	//
	// X.inorder();
  // cout << endl;

	// RBTree<int,int> Y = X;
	// for (int i=0; i < 10; i++){
	// 	X.rank(i);
	// 	X.remove(i);
	// }
	// Y.postorder();
  //   cout << endl;
	// Y.inorder();
  //   cout << endl;
	cout << "Finished without failing" << endl << endl;

}

// void test7(){
// 	int rankError = 0;
// 	int selectError = 0;
// 	int searchError = 0;
//     RBTree<int,int> X;
// 	for (int i=100100;i>=0;i--) X.insert(i,100100-i);
// 	for (int i=1;i<100100;i++) {
// 		// cout << i+1 << " is i+1" << endl;
// 		// cout << X.rank(i) << " is rank" << endl;
// 		if(X.rank(i) != i+1) rankError++; //cout << "Rank error before delete" << endl;
// 		if(X.select(i) != i-1) selectError++; //cout << "Select error before delete" << endl;
// 		if(*(X.search(i)) != 100100-i) searchError++;//cout << "Search error before delete" << endl;
// 	}
// 	printErrors("Rank",rankError);
// 	printErrors("Select",selectError);
// 	printErrors("Search",searchError);
// 	cout << "Finished without failing" << endl << endl;
// }

void test8(){
	removeIndex(13);
}

void removeIndex(int removeIndex){
	int rankError = 0;
	int selectError = 0;
	int searchError = 0;
  RBTree<int,int> X;
	int size = 100100;
  for (int i=size;i>=0;i--) X.insert(i,size-i);
	for (int i=0;i<size;i+=removeIndex) X.remove(i);
	for (int i=1;i<size-size/removeIndex;i++){

        int part1Answer = i / removeIndex;
		int answer = i+(i+(i+(i+(i+(i + i / removeIndex)/removeIndex)/removeIndex)/removeIndex)/removeIndex)/removeIndex;

		//printf("i is %d, Select %d, Rank %d, Search %d\n",i, answer, i-i/removeIndex, size-i);

        if(X.select(i) != answer){
			selectError++;
			//cout << "i is " << i << " Select error after delete " << X.select(i)  << " should be " <<  answer << " or " << part1Answer << endl;
		}
		if (i%removeIndex) {
			//cout << i << " is i" << endl;
			if(X.rank(i) != i-i/removeIndex){
                rankError++;
                //cout << "Rank error after delete " << X.rank(i) << " should be " << i << " - " << i-i/removeIndex << endl;
			}
            if(*(X.search(i)) != size-i) searchError++;// cout << "Search error after delete" << endl;
            X.remove(i);
			X.insert(i,size-i);
		}
	}
	printErrors("Rank after delete",rankError);
	printErrors("Select after delete",selectError);
	printErrors("Search after delete",searchError);
	cout << "Finished without failing" << endl << endl;
}
