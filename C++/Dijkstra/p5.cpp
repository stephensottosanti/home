#include <iostream> // cin and cout
#include <fstream> // ifstream, ofstream
#include <string> // string class
#include <iomanip> // setfill(), setw(), etc
#include <sstream> //istringstream, ostringstream
#include <vector>
#include <cctype> //isalpha islower
#include <cmath> // for infinity
#include <limits>

using namespace std;
/*************************************************************/
struct Visited {
  string name; //Name of node
  Visited *next;
  Visited(string a,  Visited *b){
    name = a;
    next = b;
  }
};
/*************************************************************/
/*************************************************************/
struct MyNode {
  string name; //Name of node
  double delayTime; //value of the node
  string toEdge;
  double distance;
  double speed;
  MyNode *next;
  MyNode(string a, double b, string c, double d, double e, MyNode *f){
    name = a;
    delayTime = b;
    toEdge = c;
    distance = d;
    speed = e;
    next = f;
  }
};
/*************************************************************/
/*************************************************************/
struct MyEdge {
  string startNode;
  string endNode;
  double dist;
  double spd;
  MyEdge *nextEdge;
  MyEdge(string a, string b, double c, double d, MyEdge *e){
    startNode = a;
    endNode = b;
    dist = c;
    spd = d;
    nextEdge = e;
  }
};
/*************************************************************/
/*************************************************************/
struct Dijkstra {
  string vertex;
  int cost;
  string prevVertex;
};
/*************************************************************/
/*************************************************************/
class MyGraph { //Graph with weighted Nodes and Edges
public:
   Visited *check;
  Dijkstra *top;
  MyEdge *headEdge;
  MyNode **head;                //adjacency list as array of pointers
  /*************************************************************/
  //pretty much a construcotr. sets head[] to all nullptr
  void setList(int num)  {
    top = new Dijkstra[num];
    check = nullptr;
    headEdge = nullptr;
    // allocate new node
    head = new MyNode*[num]();
    // initialize head pointer for all vertices
    for (int i = 0; i < num; ++i)
        head[i] = nullptr;
  }
  /*************************************************************/
  //adds the nodes that graph points too
  //Works
  void addNode(string name, double time){
    MyNode **n = head;

    if (n[0] == nullptr) {
      n[0] = new MyNode(name, time, "none", 0, 0, nullptr);
      return;
    }
    else {
      int i = 0;
      while (n[i] != nullptr) {
        ++i;
      }
      n[i] = new MyNode(name, time, "none", 0, 0, nullptr);
    }

    return;
  }
 /*************************************************************/
 //adds edges to each corresponding node
 //Works
 void addEdge(string start, string end, int distance, int speed) {
    MyEdge *e = headEdge;


    if(e == nullptr){
      headEdge = new MyEdge(start, end, distance, speed, nullptr);
    }
    else{
      while(e->nextEdge != nullptr){
       e = e->nextEdge;
      }
      e->nextEdge = new MyEdge(start, end, distance, speed, nullptr);
    }
    return;
 }
 /*************************************************************/
 //works
 void createGraph(int numNodes, int numEdges){
    MyNode **n = head;
    MyNode *node;
    MyEdge *e = headEdge;
    int i = 0;
    string findNode, currNode, findEdge;
    string temp;

    //lets add all edges to corresponding nodes
    while(e != nullptr) {
      findNode = e->startNode; //the node we want to add edge to
      findEdge = e->endNode; //the edge we want to add
      //find the correct node
      while(n[i] != nullptr) {
          node = n[i];
       //found the node we want to add an edge to
          if(findNode == node->name){
             //now we need to add the edge
             while(node->next != nullptr) {
               node = node->next;
             }
             //add edge to node with edges appropriate delay time
             node->next = new MyNode(currNode, 0, e->endNode, e->dist, e->spd, nullptr);
             break;
          }
       ++i;
      }
      e = e->nextEdge;
    }

    return;
 }
 /*************************************************************/
//finds the current value. this one finds distance
//Works
 double findValue(string start, string end, string edge, string value){
    MyNode **n = head;
    MyNode *node;
    string temp;
    int i = 0;
    double val;
    int dt;

   //find node
   while(n[i] != nullptr){
      if(start == n[i]->name){
         node = n[i];
         break;
      }
      ++i;
   }

   dt = node->delayTime;
   if(value == "delay") {
      i = 0;
      if(edge == end){
         return 0;
      }
      while(n[i] != nullptr){
         if(edge == n[i]->name){
            node = n[i];
            break;
         }
      ++i;
      }
      return node->delayTime;
   }
   else if(value == "hops") {
      return 1;
   }
   else if(value == "dist") {
      while(node != nullptr){
         if(node->toEdge == edge) {
            return node->distance;
         }
         node = node->next;
      }
   }
   else if(value == "travel") {
      while(node != nullptr){
         if(node->toEdge == edge) {
            val = node->distance / node->speed;
            return val;
         }
         node = node->next;
      }
   }
   else if(value == "total"){
      while(node != nullptr){
         if(node->toEdge == edge) {
            i = 0;
            while(n[i] != nullptr){
               if(edge == n[i]->name){
               dt = n[i]->delayTime;
               break;
               }
            ++i;
            }
            if(edge == end){
               val = (node->distance / node->speed);
               return val;
             }
            val = dt + (node->distance / node->speed);
            return val;
         }
         node = node->next;
      }
   }



    return 0;
 }
  /*************************************************************/
//changes the array and puts in new values for cost and prev
//Works
 void changeCost(string v, string prev, int newCost, int num){
    int i;
    Dijkstra *arr = top;

    for(i = 0; i < num; ++i) {
      if(arr[i].vertex == v){
         arr[i].cost = newCost;
         arr[i].prevVertex = prev;
         break;
      }
    }

    return;
 }
  /*************************************************************/
//will find the current cost found in the table
//Works
 double findCostV(string v, int size){
    double cost;
    int i;
    Dijkstra *arr = top;

    for(i = 0; i < size; ++i) {
      if(v == arr[i].vertex){
       cost = arr[i].cost;
       return cost;
      }
    }

    return 0;
 }
   /*************************************************************/
   //Works
  int isChecked(string vertex) {
   Visited *c = check;

   while(c != nullptr) {
      if(vertex == c->name){
         return 0;
      }
      c = c->next;
   }

   return 1;
  }
 /*************************************************************/
 //works
 void removeV(string v){
    Visited *c = check;
    Visited *d;


    while(c != nullptr) {
       if(v == check->name){ //the vertex to delete is the first one
         check = check->next;
         delete c;
         break;
       }
       d = c->next;
       if(v == d->name){ //found vertex we want to delete //not the first one
         c->next = d->next;
         delete d;
         break;
       }
       c = c->next;
    }

    return;
 }
 //  /*************************************************************/
 //Works
 string findNextVertex(string current, int numNodes, string prev){
    MyNode **n = head;
    MyNode *node;
    Dijkstra *arr = top;
    double costV;
    double cost;
    int i = 0;
    int j;
    string temp;
    string done = "done";
    string nextCheck;
    int check;
    int move = 0;

    if(prev == "nada"){
       return "nada";
    }

    while(n[i] != nullptr){
      if (current == n[i]->name) { //found the vertex we want to check
         node = n[i];
         break;
       }
      ++i;
    }

   //check its edges
   /*************************************************************/
   if(node->next == nullptr){ //if this vertex has no Edges
      for(j = 0; j < numNodes; ++j) { //find the node within the table to find prevNode
         if(node->name == arr[j].vertex){ //now if nada were done
            nextCheck = arr[j].prevVertex;
            return findNextVertex(nextCheck, numNodes, nextCheck);
         }
      }
   }
   /*************************************************************/
   // //otherwise lets find next edge to Dijkstra
   node = node->next; //because front node isnt what we wanna check
   if(node->next == nullptr) { //if there is only 1 edge to compare to and it hasn't been checked
      check = isChecked(node->toEdge);
      if(check == 1) { //this edge was already checked;
       for(j = 0; j < numNodes; ++j) { //find the node within the table to find prevNode
         if(n[i]->name == arr[j].vertex){ //now if nada were done
            nextCheck = arr[j].prevVertex;
            return findNextVertex(nextCheck, numNodes, nextCheck);
         }
       }
      }
      return node->toEdge;
   }
   //more than one edge
   //compare the other edges and find the smallest cost
   while (node != nullptr) {

      check = isChecked(node->toEdge);

      if(check == 1) { //this edge was already checked;
         node = node->next;
      }
      else{
         for(i = 0; i < numNodes; ++i) { //find the first cost to compare
            if(node->toEdge == arr[i].vertex){
               costV = arr[i].cost;
               done = node->toEdge;
               node = node->next;
               move = 1;
               break;
            }
         }
         while (node != nullptr) {
            check = isChecked(node->toEdge);
            if(check == 1) { //this node was already checked;
               //node = node->next;
            }
            else{
               for(i = 0; i < numNodes; ++i) { //find next cost to compare //also check if it has been visited
                  if(node->toEdge == arr[i].vertex){
                     cost = arr[i].cost;
                  }
               }
               if(cost < costV) { //compare them. maybe switch
                  costV = cost;
                  done = node->toEdge;
               }
            }
            node = node->next;
         }
      }
   }

   //were moving back and all of this vertexes edges have been checked  but were not at start
   if(move == 0) {
      for(j = 0; j < numNodes; ++j) { //find the node within the table to find prevNode
         if(n[i]->name == arr[j].vertex){ //now if nada were done
            nextCheck = arr[j].prevVertex;
            return findNextVertex(nextCheck, numNodes, nextCheck);
         }
       }
   }

    return done;
 }
//  /*************************************************************/
//Works
 void runDijkstra(string vertex, string end, int numNodes, string value){
      MyNode **n = head;
      MyNode *node;
      string temp, theNode, theEdge;
      int i = 0;
      double cost;
      double inf;


      //finding the vertex we want to visit
      for(i = 0; i < numNodes; ++i) {
         [&]{
         if (vertex == n[i]->name) { //found the vertex we want to visit
            //lets use dijkstra on it
            node = n[i];
            if(node->next == nullptr){ //if this vertex has no Edges so we can delete it
               return;
            }
            node = node->next;
             while (node != nullptr) { //finds shorter path for every edge if there is one
               //find cost from vertex to current edge we're looking at
               cost = findCostV(vertex, numNodes) + findValue(vertex, end, node->toEdge, value);
               //find the value of the node we might change
               inf = findCostV(node->toEdge, numNodes);
               if(cost < inf){
                 changeCost(node->toEdge, vertex, cost, numNodes);
               }
               node = node->next;
             }
            return;
         }
         }();
      }

      removeV(vertex);
      vertex = findNextVertex(vertex, numNodes, "none");

      if(vertex == "nada"){
         return;
      }

      runDijkstra(vertex, end, numNodes, value); //else run it again with new vertex;


      return;
   }
// /*************************************************************/
//Works
 void dijkstraDistance(string start, string end, int numNodes){
   string value = "dist";

   setTable(start, numNodes);
   runDijkstra(start, end, numNodes, value);

   print(start, end, numNodes, value);

 }
// /*************************************************************/
//Works
void dijkstraDelay(string start, string end, int numNodes){
   string value = "delay";

   setTable(start, numNodes);
   runDijkstra(start, end, numNodes, value);

   print(start, end, numNodes, value);

}
//   /*************************************************************/
//Works
void dijkstraExpectedTravel(string start, string end, int numNodes){
   string value = "travel";

   setTable(start, numNodes);
   runDijkstra(start, end, numNodes, value);

   print(start, end, numNodes, value);
 }
//   /*************************************************************/
//Works
void dijkstraExpectedTotal(string start, string end, int numNodes){
   string value = "total";

   setTable(start, numNodes);
   runDijkstra(start, end, numNodes, value);

   print(start, end, numNodes, value);
}
//   /*************************************************************/
   //The number of edges on the path
void dijkstraHops(string start, string end, int numNodes){
   string value = "hops";

   setTable(start, numNodes);
   runDijkstra(start, end, numNodes, value);

   print(start, end, numNodes, value);
}
/*************************************************************/
/*************************************************************/
void setTable(string start, int numNodes){
//works
    MyNode **n = head;
    Dijkstra *table = top;
    Visited *c = check;
    string temp;
    int i;
    double cost = 0;
    double max = 100000000;


    for(i = 0; i < numNodes-1; ++i) {
      c = check;
      temp = n[i]->name;
      if(temp == start){
       cost = 0;
      }
      else {
       cost = max;
      }

      table[i].vertex = temp;
      table[i].cost = cost;
      table[i].prevVertex = "nada";
      //cout << table[i].vertex << " " << table[i].cost << " " << table[i].prevVertex << endl;

      //while also creating the list of checked names
      if (c == nullptr) {
         check = new Visited(temp, nullptr);
      }
      else {
         while (c->next != nullptr) {
          c = c->next;
         }
         c->next = new Visited(temp, nullptr);
       }
    }
}
/*************************************************************/
/*************************************************************/
 void print(string start, string end, int numNodes, string value){
   //run through the table and print out the result
    Dijkstra *table = top;
    int cost = 0;
    vector<string> track;
    string temp1;
    string temp = end;
    int i;

   // for(i = 0; i < numNodes-1; ++i) {
   //    cout << table[i].vertex << " " << table[i].cost << " " << table[i].prevVertex << endl;
   //  }

   //will set up vertex to be able to print path of shortest distance
    for(int i = 0; i < numNodes; ++i) {
      temp1 = table[i].vertex;
      if(temp == temp1) { //found the end or prev node. Add to tracing vector
         track.push_back(temp);
         temp = table[i].prevVertex;
         i = 0;
      }
      if(temp == start){ //if we've reached the start we break
         track.push_back(temp);
         break;
      }
    }

    //to find the cost
    for(int i = 0; i < numNodes; ++i) {
      temp = table[i].vertex;
      if(temp == end) { //found the end or prev node. Add to tracing vector
       cost = table[i].cost;
       break;
      }
    }

    //print
   if(value == "delay") {
      cout << "Shortest delay time: ";
   }
   else if(value == "hops") {
      cout << "Fewest hops: ";
   }
   else if(value == "dist") {
      cout << "Shortest distance: ";
   }
   else if(value == "travel") {
      cout << "Shortest expected traveling time: ";
   }
   else if(value == "total"){
      cout << "shortest expected total time: ";
   }

   cout << cost << endl;

   cout << "Path: ";
   int size = track.size() - 1;

   for(i = size; i >= 0; --i){
      cout << track.at(i);
      if (i == 0) break;
      cout << "->";
    }
    cout << endl << endl;
 }
};
/*************************************************************/
/*************************************************************/
int main(int argc, char* argv[]) {
  MyGraph graph;

  ifstream Nodes;
  int numNodes = 0;

  ifstream Edges;

  string node = " ";
  int dt = 0;

  //Check number of argument. It should only be 4
  // if (argc > 2) {
  //   cout << endl << "Usage: myprog.exe inputFileName" << endl;
  //   return 1; // 1 indicates error
  // }
  //
  /*************************************************************/
   Nodes.open(argv[1]); // Try to open file
  // if (!Paragraph.is_open()) {
  //   cout << "Could not open file " << argv[1] << "." << endl;
  //   return 1; // 1 indicates error
  // }
  //
   Edges.open(argv[2]); // Try to open file
  // if (!Query.is_open()) {
  //   cout << "Could not open file " << argv[2] << "." << endl;
  //   return 1; // 1 indicates error
  // }
  /*************************************************************/

//Adds node names and they're corresponding delay times
  while(!Nodes.eof()) {
    Nodes >> node;
    Nodes >> dt;
    ++numNodes;
  }
  Nodes.clear();                 // clear fail and eof bits
  Nodes.seekg(0, ios::beg);     //back to beginning
  //call the Constructor
  graph.setList(numNodes);
  //lets add the nodes
  while(!Nodes.eof()) {
    Nodes >> node;
    Nodes >> dt;
    graph.addNode(node, dt);
  }


 string start;
 string end;
 double distance;
 double speed;
 int numEdges = 0;

 while(!Edges.eof()) {
    Edges >> start;
    Edges >> end;
    Edges >> distance;
    Edges >> speed;
    graph.addEdge(start, end, distance, speed);
    ++numEdges;
 }


  graph.createGraph(numNodes, numEdges);

   //cout<< "Please enter a pair of nodes for source and destination: " << endl << endl;
   cin >> start;
   cin >> end;

   graph.dijkstraDistance(start, end, numNodes);
   graph.dijkstraDelay(start, end, numNodes);
   graph.dijkstraExpectedTravel(start, end, numNodes);
   graph.dijkstraExpectedTotal(start, end, numNodes);
   graph.dijkstraHops(start, end, numNodes);



  return 0;
}
