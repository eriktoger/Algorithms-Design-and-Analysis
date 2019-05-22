#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h> 

using namespace std;
/*
skapar en vector av nodes.
varje node har:
ett id (usprung)
NodeLabels (sitt ursprung + övriga som den ätit upp)
Edges. hur den sitter ihop med andra.

Målet är att hitta min cuts. 
Så det join gör är att ta en node random och sedan
kolla bland dennes edges. En edge/node väljs random.
Den node äts up av den en första noden.
Första noden har nu andra nodens Nodelabels bland sina NodeLabels och dens edges bland sinae edges.
Self-loops och dubletter tas bort.

Detta görs till det finns två nodes kvar.
Sedan kollar vi hur många edges det finns emllan.
Det största av både gäller (då vi har tagit bort dubletter)

slutligen kan scriptet köras limit gånger. Det lägsta talet sparas (minEdges).

*/

// class Node

class Node{
private:
int nodeId;
vector <int> nodeLabels;
vector <int> edges;
public:
Node();
Node(vector<int>, vector<int>);
//const Node& operator=(const Node& n);

~Node();

vector <int> hamtaNodeLabels();
void laggTillNodeLabel(int NL);

vector <int> hamtaEdges();
void laggTillEdges(int E);

int hamtaNodeId();

void ersattEdges(vector <int> nyEdges);
void ersattNodeLabels(vector <int> nyNodelabels);

//void join(Node &,Node,vector<Node> &VL);
void join(Node,vector<Node> &VL);
};

// Node
Node::Node(){
  nodeId = 0;
  vector<int> tempNL;
  vector<int> tempE;
  this->nodeLabels = tempNL;
  this->edges = tempE; 
}

Node::Node(vector<int> NL,vector<int> E){
  this -> nodeId = NL.front(); //första 
  this->nodeLabels = NL;
  this->edges = E; 
}
/*
const Node& Node::operator=(const Node& n){
  if (this !=&n){
    nodeId =n.nodeId;
    nodeLabels = n.nodeLabels;
    edges = n.edges;
  }
  return *this;
}
*/

Node::~Node(){}

vector <int> Node::hamtaNodeLabels(){
  return nodeLabels;
}

vector <int> Node::hamtaEdges(){
  return edges;
}

int Node::hamtaNodeId(){
  return nodeId;
}

void Node::laggTillNodeLabel(int NL){
  nodeLabels.push_back(NL);
  // ska vi kolla om den finns?
}

void Node::laggTillEdges(int E){
  edges.push_back(E);
  // ska vi kolla om den finns?
}

void Node::ersattEdges(vector <int> nyEdges){
  edges = nyEdges;
}

void Node::ersattNodeLabels(vector <int> nyNodeLabels){
  nodeLabels = nyNodeLabels;
}



void Node::join(Node N2,vector <Node> &VL){

  vector<int> tempNL;

  //kopierar NodeLabels från N2 till N1 
  for( int i = 0; i<N2.hamtaNodeLabels().size();i++){

    laggTillNodeLabel(N2.hamtaNodeLabels()[i] );
  }

  // kopierar Edges från N2 till N1
  for( int i = 0; i<N2.hamtaEdges().size();i++){
    laggTillEdges(N2.hamtaEdges()[i] );
  }

  // tar bort alla dubletter.
  
  tempNL = hamtaEdges();
  sort( tempNL.begin(), tempNL.end() );
  tempNL.erase( unique( tempNL.begin(), tempNL.end() ), tempNL.end() );
  ersattEdges(tempNL);

 // ta bort alla self-loopes
  // dvs alla edges som finns i NodeLabels.
  vector <int> tempE = hamtaEdges();
  
  for(int i =0;i<hamtaNodeLabels().size();i++){
    tempE.erase(std::remove(tempE.begin(),tempE.end(),hamtaNodeLabels()[i]),tempE.end());    
  }  
  
ersattEdges(tempE);

 //raderar N2
 for (int i = 0; i< VL.size();i++){
    if(VL[i].hamtaNodeId() == N2.hamtaNodeId() ){
      VL.erase (VL.begin()+i);
      break;
    } 
}
//cout<<"i"<<endl;
}

int main() {
  cout<<"prgrammet startar"<<endl;
  srand(time(NULL));
  string rad;
  
  vector <Node> VofNodes;
  //vector <Node> VofNodes1;
  vector <int> VofNodeLabels;
  vector <int> VofEdges;
  int firstNumber;
  int tempNumber;
  int randomNumber1;
  int randomNumber2;
  int edge1;
  int edge2;
  int minEdges= 999999;
  int maxEdges;
  int limit =1000;
  ifstream is("krugerMinCut.txt");
  
 if(is.fail()){
    cout<<endl;
    cout<< "Filnamnet du angav hittades inte"<<endl;
    cout<<endl;
    cout<<"programmet avslutas"<<endl;
    return 0;
  }
  int counter=0;
  int counter1=0;
  while(!is.eof()){
  counter1=0;  
  VofNodeLabels.clear();
  VofEdges.clear();

  getline(is,rad);
  stringstream ss(rad);
  ss>> firstNumber;
  VofNodeLabels.push_back(firstNumber);
  while(!ss.eof()){
    ss>>tempNumber;
    VofEdges.push_back(tempNumber);
    counter1++;
  if (counter1>230){
    cout<<"break ss"<<endl;
    break;
    }
  }
  VofNodes.push_back(Node(VofNodeLabels,VofEdges));
  //cout<< rad<<endl;
  counter++;
  if (counter>230){
    cout<<"break"<<endl;
    break;
    }
  }
  
  int counter3 =0;
  //cout<<VofNodes.size()<<endl;
  for(int k=0; k<limit;k++){
    //cout<<"k"<<endl;
    vector <Node> VofNodes1 = VofNodes;  
    
    while(VofNodes1.size()!=2){

      //cout<<"1"<<endl;
      int indexRN1;
      int indexNodeId1;
      int indexRN2NodeId;
      int node1Id;
      int node2Id;
      bool hittad = false;
      
      // vi slumpar fram en node.
      randomNumber1 = rand() % VofNodes1.size();
      node1Id =  VofNodes1[randomNumber1].hamtaNodeId();

      // vi slumpar fram vilken node som ska joina
      randomNumber2 = rand () % VofNodes1[randomNumber1].hamtaEdges().size();
      
      node2Id =  VofNodes1[randomNumber1].hamtaEdges()[randomNumber2];

      // var finns node2? den kan vara uppäten av en annan node.
      for(int i = 0;i<VofNodes1.size();i++){
        for(int j=0; j < VofNodes1[i].hamtaNodeLabels().size();j++){
          if(node2Id ==VofNodes1[i].hamtaNodeLabels()[j] ){
            indexRN2NodeId = i;
          }
        }
      }
      /*
      cout<<endl;
      
      cout<<"Före join"<<endl;

      cout<<"nodeId 1 "<<VofNodes1[randomNumber1].hamtaNodeId()<<endl;
      cout<< "nodId 1 nodeLabels ";
      for(int i = 0;i<VofNodes1[randomNumber1].hamtaNodeLabels().size();i++){
        cout<< VofNodes1[randomNumber1].hamtaNodeLabels()[i]<<" ";
      }
      cout<<endl;
      cout<< "nodId 1 edges ";
      for(int i = 0;i<VofNodes1[randomNumber1].hamtaEdges().size();i++){
        cout<< VofNodes1[randomNumber1].hamtaEdges()[i]<<" ";
      }
      cout<<endl;
      

      cout<<"nodeId 2 " << VofNodes1[indexRN2NodeId].hamtaNodeId()<<endl;

      cout<< "nodId 2 nodeLabels ";
      for(int i = 0;i<VofNodes1[indexRN2NodeId].hamtaNodeLabels().size();i++){
        cout<< VofNodes1[indexRN2NodeId].hamtaNodeLabels()[i]<<" ";
      }
      cout<<endl;
      cout<< "nodId 2 edges ";
      for(int i = 0;i<VofNodes1[indexRN2NodeId].hamtaEdges().size();i++){
        cout<< VofNodes1[indexRN2NodeId].hamtaEdges()[i]<<" ";
      }
      cout<<endl;

      */
      VofNodes1[randomNumber1].join(VofNodes1[indexRN2NodeId],VofNodes1);

      /*
      cout<<endl;
      cout<<"efter join"<<endl;
      // nu har ju VofNodes1 ändrats.

      for(int i = 0;i<VofNodes1.size();i++){
        if(VofNodes1[i].hamtaNodeId() == node1Id){
             indexNodeId1 = i;
             break;
        }
      }

      cout<<"nodeId 1 "<<VofNodes1[indexNodeId1].hamtaNodeId()<<endl;
      cout<< "nodId 1 nodeLabels ";
      for(int i = 0;i<VofNodes1[indexNodeId1].hamtaNodeLabels().size();i++){
        cout<< VofNodes1[indexNodeId1].hamtaNodeLabels()[i]<<" ";
      }
      cout<<endl;
      cout<< "nodId 1 edges ";
      for(int i = 0;i<VofNodes1[indexNodeId1].hamtaEdges().size();i++){
        cout<< VofNodes1[indexNodeId1].hamtaEdges()[i]<<" ";
      }
      cout<<endl;
      */

  }
  // nu finns det bara 2 nodes kvar
  edge1 = VofNodes1[0].hamtaEdges().size();;
  edge2 = VofNodes1[1].hamtaEdges().size();
  
  
  maxEdges = max(edge1,edge2);
  minEdges=min(minEdges,maxEdges );

  cout <<minEdges<<endl;
  }
 
//cout <<minEdges<<endl;
cout<<"prgrammet avslutas"<<endl;
}