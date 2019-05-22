#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h> 
using namespace std;


/*
jag borde gå igenom denna igen
Jag borde lägga till en heap

*/

class Node{
  
  private:
  int nodeID;

  // denna ska var en heap istället
  vector < pair <int,int> > edges;

  bool beenVisited;
  public:
  Node(int nodeID,vector < pair <int,int> > edges);
  Node();
  int hamtaNodeID();
  vector < pair <int,int> > hamtaEdges();
  void updateEdges(int add);
  void join(Node node2);
  void visited();
  bool hamtaVisited();

};

Node::Node(int newNodeID,vector < pair <int,int> > newEdges){
  nodeID = newNodeID;
  edges = newEdges;
  beenVisited = false;
}

Node::Node(){
  nodeID =0;
}

int Node::hamtaNodeID(){
  return nodeID;
}
vector < pair <int,int> > Node::hamtaEdges(){
  return edges;
}

// varje node for sin väg adderad
// då vi utgår från node 1
void Node::updateEdges(int add){
  for(int i=0;i<edges.size();i++){
    edges[i].second+=add;
  }
}

void Node::visited(){
  beenVisited = true;
}

bool Node::hamtaVisited(){
  return beenVisited;
}

//  lägger över alla edges och tar bort dubbletter
// jag hade tur att dubbleten med den långa vägen tas bort
// jag borde göra om vector vector int  edges till heap edges
void Node::join(Node node2){
  int lastEdge = 0;
  
  for(int i =0;i<node2.edges.size();i++){
    edges.push_back(node2.hamtaEdges()[i]);
  }
  sort(edges.begin(),edges.end());
  //ta bort 1? räcker att den är visited
  for(int i=0;i<edges.size();){
    if(lastEdge==edges[i].first){
      edges.erase(edges.begin()+i);
      // andra gången jag stöter på ett objekt så erase
      // om något försvinner så behöver vi inte öka.
    }
    else{
      i++; // increment
    }
    lastEdge= edges[i-1].first;

  }

}

int main() {
  const int numberOFNodes = 201;
  int shortestPathLength[numberOFNodes];
  int tempNodeID;
  Node nodeList[numberOFNodes];
  string rad;
  int pos;
  char space ='	'; // är det en tabb? kopierat från graph.txt
  vector<int> positions;
  vector <pair <int,int> > tempNodeVector;
  int tempEdge;
  int tempWeight;
  Node tempNode;
  int counterNode =numberOFNodes;
  int shortestPath;
  int tempShort;
  int tempNextNode;
  int nextNode =1;

/*

Läser in filen och gör om till nodes

*/
  ifstream input;
	input.open("graph.txt");

  int counter =0;
  while (!input.eof())
	{
    getline(input,rad);
   
    pos = 0;
    counter = 0;
    positions.clear();
    while(pos!=-1){
     
      pos = rad.find(space,pos+1);
      positions.push_back(pos);
       
      pos = rad.find(',',pos+1);
      
      positions.push_back(pos);
      counter++;
      if(counter>100){
        cout<<"break"<<endl;
        break;
      }

    }
    tempNodeID = stoi(rad.substr(0,positions[0]) );
    
    tempNodeVector.clear();
    for(int i =0;i<positions.size()-2;i=i+2){
      
      tempEdge = stoi(rad.substr(positions[i],positions[i+1]-positions[i]) );
      tempWeight = stoi(rad.substr(positions[i+1]+1,positions[i+2]-positions[i+1]) );
      
     tempNodeVector.push_back(make_pair (tempEdge,tempWeight));
    }
       nodeList[tempNodeID] = (Node(tempNodeID,tempNodeVector));

    positions.clear();
   
	}

	input.close();

  /*
  
  börjar på node nr 1 och "äter sig" igenom hela grafen

  */

   nodeList[1].visited();
   shortestPathLength[1]=0;
  
   while(counterNode--){
     shortestPath= -1;

     for(int i =0;i<nodeList[1].hamtaEdges().size();i++){
     
      tempNextNode= nodeList[1].hamtaEdges()[i].first; 
      tempShort =nodeList[1].hamtaEdges()[i].second;
      
      // första gången så sätter vi den automatiskt
      if( (shortestPath == -1) & !nodeList[tempNextNode].hamtaVisited() ){
        shortestPath = tempShort;
        nextNode = tempNextNode;
      }
      // men i fortsättning så måste den var mindre
      if((tempShort < shortestPath ) & !nodeList[tempNextNode].hamtaVisited() ){
        shortestPath = tempShort;
        nextNode = tempNextNode;
      }
    }
   
    shortestPathLength[nextNode] =shortestPath;
  
    nodeList[nextNode].visited();
    nodeList[nextNode].updateEdges(shortestPath);
    nodeList[1].join(nodeList[nextNode]);
    
   } // end while

   /*
   
   printar ut de avstånd vi är intresserade av
   
   */
  
  cout<<endl;
  cout<<7 <<  " "<<shortestPathLength[7]<<endl;
  cout<<37 <<  " "<<shortestPathLength[37]<<endl;
  cout<<59 <<  " "<<shortestPathLength[59]<<endl;
  cout<<82 <<  " "<<shortestPathLength[82]<<endl;
  cout<<99 <<  " "<<shortestPathLength[99]<<endl;
   cout<<115 <<  " "<<shortestPathLength[115]<<endl;
  cout<<133 <<  " "<<shortestPathLength[133]<<endl;
  cout<<165 <<  " "<<shortestPathLength[165]<<endl;
  cout<<188 <<  " "<<shortestPathLength[188]<<endl;
  cout<<197 <<  " "<<shortestPathLength[197]<<endl;
   
 // 2599,2610,2947,2052,2367,2399,2029,2442,2505,3068

}