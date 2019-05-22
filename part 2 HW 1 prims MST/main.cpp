#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <utility>
using namespace std;



bool compare(const pair<int, int>&i, const pair<int, int>&j);

int main() {
  std::cout << "Hello World!\n";
  ifstream input;
	input.open("edges.txt");
  int numberOfNodes;
  int node1;
  int node2;
  int weight;
  int saftyCounter =0;
  long int sumLength = 0;
  input >> numberOfNodes;

  vector < pair <int,int> >  listOfNodes[numberOfNodes+1];
  bool notVisited[numberOfNodes+1];
  for(int i =0;i<=numberOfNodes;i++){
    notVisited[i] = true;
  }

  input >> numberOfNodes; // äter upp vertices
  
  //lägger in varje edge till rätt node
  while(!input.eof()){
    saftyCounter++;
    if (saftyCounter> 3000){
      cout<<"hej"<<endl;
      break;
    }
    input >> node1;
    //cout<< node1<<endl;
    input >> node2;
    input >> weight;
    listOfNodes[node1].push_back(make_pair(node2,weight));
    listOfNodes[node2].push_back(make_pair(node1,weight));
  }
  notVisited[1] = false; //utgår från 1
  numberOfNodes--;
  // så nu går vi igenom 

    
  while(numberOfNodes--){
    
    // vi sorterar så vi tar den med lägst edge.

    sort(listOfNodes[1].begin(),listOfNodes[1].end(),compare);

    // vi kollar igenom vår vector av pairs.
    for(int i=0;i<listOfNodes[1].size();i++ ){
      //cout<<listOfNodes[1][i].first<<endl;

      // pair kan ju inte tidigare vare besökt
      if(notVisited[listOfNodes[1][i].first]){
        //cout<<"hej"<<endl;
        
        // nu har vi besökt noden.
        notVisited[listOfNodes[1][i].first] = false;
        
        //  vi går igenom den nya nodens edges och lägger till de som vi inte redan har sett.
        for(int j = 0;j<listOfNodes[listOfNodes[1][i].first].size();j++){

          // endast de vi inte har sett läggs till
          if(notVisited[listOfNodes[listOfNodes[1][i].first][j].first]){
            listOfNodes[1].push_back(make_pair( listOfNodes[listOfNodes[1][i].first][j].first , listOfNodes[listOfNodes[1][i].first][j].second) );
          } // end if notVisited again
        } // end for int j
        sumLength += listOfNodes[1][i].second;
        break;
      }
      else{
        //här borde pairet tas bort
        //men då ska inte i öka 
      } // end if notVisited
      
    } // end for listOfNodes[1].size()
    
    

  } // end while
  cout<<sumLength<<endl;
 
  


}


bool compare(const pair<int, int>&i, const pair<int, int>&j){
  
  if(i.second < j.second){
    return true;
  }
  else{
    return false;
  }

}