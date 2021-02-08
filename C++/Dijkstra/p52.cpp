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
  //initializes the check table
  // Dijkstra setTable(string start, int numNodes){
  //   double inf = numeric_limits<double>::infinity();
  //   string temp;
  //   int i;
  //   int cost;
  //   //initialize table to 0 and infinty
  //   Dijkstra *table = top; //table to keep track of costs
  //   for(i = 0; i < numNodes; ++i) {
  //     temp = n[i]->name;
  //     if(temp == start){
  //       cost = 0;
  //     }
  //     else {
  //       cost = inf;
  //     }
  //
  //     table[i].vertex = temp;
  //     table[i].cost = cost;
  //     table[i].prevVertex = "nada";
  //   }
  //   return table;
  // }
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
 double findDelay(string vertex){
    MyNode **h = head;
    int i =0;
    double x;
    string temp;

   while(h[i] != nullptr) {
      temp = h[i]->name;
      if(vertex == temp){
         cout << "got it" << endl << i << h[i]->delayTime << endl;
         x = h[i]->delayTime;
         break;
      }
      ++i;
    }
    return x;
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
//  /*************************************************************/
//  //finds the current value. this one finds distance
//Works
 double findValue(string start, string node, string edge){
    MyNode **n = head;
    string temp;
    double cost = 0;
    int i = 0;

    //the cost of the starting vertex is 0
    if(start == edge) {
      return cost;
    }
    else{
      //find node that contains the edge
      while(n[i] != nullptr){
       temp = n[i]->name;
       //find the node
       if(temp == node){
          n[i] = n[i]->next;
          while(n[i] != nullptr){
            temp = n[i]->toEdge;
            //found the edge so lets return the distance
            if(temp == edge){
             cost = n[i]->distance;
             return cost;
            }
            n[i] = n[i]->next;
          }
       }
       ++i;
      }
    }

    return 0;
 }
//  /*************************************************************/
//  //changes the array and puts in new values for cost and prev
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
//  /*************************************************************/
//  //will find the current cost found in the table
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
//  /*************************************************************/
 void runDijkstraDistance(string vertex, int numNodes){
      MyNode **n = head;
      MyNode *node;
      string temp, theNode, theEdge;
      int i = 0;
      double cost;
      double inf;


      //finding the vertex we want to visit
      while(n[i] != nullptr){
         if (vertex == n[i]->name) { //found the vertex we want to visit
            //lets use dijkstra on it
            node = n[i];
            if(node->next == nullptr){ //if this vertex has no Edges so we can delete it
               break;
            }
            node = node->next;
             while (node != nullptr) { //finds shorter path for every edge if there is one
               //find cost from vertex to current edge we're looking at
               cost = findCostV(vertex, numNodes) + node->distance;
               //find the value of the node we might change
               inf = findCostV(node->toEdge, numNodes);
               if(cost < inf){
                 changeCost(node->toEdge, vertex, cost, numNodes);
               }
               node = node->next;
             }
            break;
         }
       ++i;
      }

      // removeV(vertex);
      // Visited *x = check;
      // if(x == nullptr) {
      //    return; //no more verts to check
      // }

      vertex = findNextVertex(vertex, numNodes);
      cout << vertex << endl;
      // if(vertex == "done") {
      //    return; //thats the end of dijkstra
      // }

      //runDijkstraDistance(vertex, numNodes); //else run it again with new vertex;


      return;
    }
//  /*************************************************************/
 string findNextVertex(string current, int numNodes){
    MyNode **n = head;
    MyNode *node;
    Dijkstra *arr = top;
    double cost, costV;
    int i, j;
    string temp;
    string done = "done";
    string nextCheck;
    int check;

    cout << "finding next" << endl;

    while(n != nullptr){
      if (current == n[i]->name) { //found the vertex we want to check
         node = n[i];
         /*************************************************************/
         // if(node->next == nullptr){ //if this vertex has no Edges
         //    for(j = 0; j < numNodes; ++j) { //find the node within the table to find prevNode
         //       if(node->name == arr[j].vertex){ //now if nada were done
         //          if(arr[j].prevVertex == "nada"){
         //             return done;
         //          }
         //          nextCheck = arr[j].prevVertex;
         //          return findNextVertex(nextCheck, numNodes);
         //       }
         //    }
         // }
         /*************************************************************/
         //otherwise lets find next edge to Dijkstra
         node = node->next; //because front node isnt what we wanna check
         cout << node->name << endl;
         check = isChecked(node->toEdge);
         check = 0;
         cout << check <<endl;
         if(check == 1) { //this node was already checked;
            for(j = 0; j < numNodes; ++j) { //find the node within the table to find prevNode
               if(node->toEdge == arr[j].vertex){ //now if nada were done
                  if(arr[j].prevVertex == "nada"){
                     return done;
                  }
                  nextCheck = arr[j].prevVertex;
                  return findNextVertex(nextCheck, numNodes);
               }
            }
         }
         /*************************************************************/
         // //if it wasn't checked
         // for(i = 0; i < numNodes; ++i) { //find the first cost to compare
         //    if(node->toEdge == arr[i].vertex){
         //       costV = arr[i].cost;
         //    }
         // }
         // //if there is only 1 edge to compare to
         // if(node->next == nullptr) {
         //    return node->toEdge;
         // }
         // //compare the other edges and find the smallest cost
         // //more than 1 edge
         // temp = node->toEdge;
         // while (node->next != nullptr) {
         //    node = node->next;

         //    for(i = 0; i < numNodes; ++i) { //find another cost to compare
         //       if(node->toEdge == arr[i].vertex){
         //          cost = arr[i].cost;
         //       }
         //    }

         //    //change next vertex if cost is less than current vertex
         //    if(cost < costV) {
         //       temp = node->toEdge;
         //    }
         //  }
         }
       ++i;
      }

    return temp;
 }
  /*************************************************************/
  int isChecked(string vertex) {
   Visited *c = check;

   while(c != nullptr) {
      if(vertex == c->name){
         cout << c->name;
         return 0;
      }
   }

   return 1;
  }
 /*************************************************************/
 void removeV(string v){
    Visited *c = check;
    Visited *temp;

    //this means there is only one value left so it has to be it
    if(c->next == nullptr){
      check = nullptr;
      delete(c);
      return;
    }
    //more than one
    while(c->next != nullptr) {
       temp = c->next;
       if(v == temp->name){ //found vertex we want to delete
          c->next = temp->next;
          delete(temp);
       }
       c = c->next;
    }

    return;
 }
 /*************************************************************/
 void dijkstraShort(string start, string end, int numNodes){
    MyNode **n = head;
    Visited *c = check;
    string visited[numNodes];
    string temp;
    int i;
    double cost = 0;
    double max = 1000000;

    //table to keep track of costs
    //initialize table to 0 and infinty
    Dijkstra *table = top;

    for(i = 0; i < numNodes-1; ++i) {
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
      cout << table[i].vertex << endl;
      //while also creating the list of checked names
      // if (check == nullptr) {
      //    check = new Visited(temp, nullptr);
      // }
      // else {
      //    while (c->next != nullptr) {
      //     c = c->next;
      //    }
      //    c->next = new Visited(temp, nullptr);
      //  }
    }


    string vertex = start;
    //start with the first vertex
    //run Dijkstra for every vertex
    runDijkstraDistance(vertex, numNodes);

    for(i = 0; i < numNodes-1; ++i) {
      cout << table[i].vertex << " " << table[i].cost << " " << table[i].prevVertex << endl;
    }

   //  //run through the table and print out the result
   //  cost = 0;
   //  vector<string> track;

   //  //will find the cost
   //  for(i = 0; i < numNodes; ++i) {
   //    temp = table[i].vertex;
   //    //if we've reached the start we break
   //    if(end == temp){
   //     cost = table[i].cost;
   //     break;
   //    }
   //  }


   //  temp = end;
   //  string temp1;
   //  //will set up vertex to be able to print path of shortest distance
   //  for(int i = 0; i < numNodes; ++i) {
   //    temp1 = table[i].vertex;
   //    //found the end or prev node. Add to tracing vecor
   //    if(temp == temp1) {
   //     track.push_back(temp);
   //     temp = table[i].prevVertex;
   //     i = 0;
   //    }
   //    //if we've reached the start we break
   //    if(temp == start){
   //     break;
   //    }
   //  }


   //  cout << "shortest distance: " << cost << endl;
   //  cout << "Path: ";
   //  int size = track.size() - 1;

   //  for(i = size; i >= 0; --i){
   //    cout << track.at(i);
   //    if (i == 0) break;
   //    cout << "->";
   //  }


 }

   // /*************************************************************/

//   /*************************************************************/
//   //find the shortest distance with only delay time
//   void DijkstraDelayTime(){
//
// }
//   /*************************************************************/
//   //shortest expected travel time using distance/speed ratio for each edge
//   void DijkstraExpectedTravel(){
//
// }
//   /*************************************************************/
//   //shortest expected total time using delaytime and distance/speed ratio
//   void DijkstraExpectedTotal(){
//
// }
//   /*************************************************************/
//   //The number of edges on the path
//   void DijkstraHops(){
//
// }
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


 cout<< "Please enter a pair of nodes for source and destination: " << endl;
 cin >> start;
 cin >> end;

 graph.dijkstraShort(start, end, numNodes);







  return 0;
}
