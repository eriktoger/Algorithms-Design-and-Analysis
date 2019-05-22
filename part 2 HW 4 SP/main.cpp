#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <utility>
#include <map>
using namespace std;

// tanken är att bara ha två 2d matriser
// som jobbar omvartannat så slipper vi tusen stycken
int main() {
 std::cout << "Hello World!\n";
  map < vector <int>, int> mapValue;
  int firstArray[1001][1001];
  int secondArray[1001][1001];
  for(int i=0;i<1001;i++){
    for(int j=0;j<1001;j++){
      firstArray[i][j] = 999999;
      secondArray[i][j] = 999999;
    }
  }


  cout<<"klar"<<endl;
  
  int tempFirstNode;
  int tempSecondNode;
  int tempWeight;
  int nrOfNodes;
  int nrOfEdges;
  int answerShortPath= 99999;
  int i,j,k;
  vector <int> tempEdge;
  vector <int> edgesForMap;
  vector < vector<int> > edges;
  ifstream input; 
  input.open("g3.txt");
   if( input.fail() ){
    cout<<"filen hittades inte"<<endl;
    return 1;
  }
  else{
    cout<<"läser in tal"<<endl;
  }
  input >> nrOfNodes; // 
  input >> nrOfEdges;
  i = nrOfEdges;
  j = nrOfEdges;
  k = nrOfEdges;

  while(!input.eof()){
    input >> tempFirstNode;
    input >> tempSecondNode;
    input >> tempWeight;
    firstArray[tempFirstNode][tempSecondNode] = tempWeight;
  }

int tempAnswer;
for(int k=1;k<=nrOfNodes;k++){
  //cout<<"k nr "<<k<<endl;
  for(int i=1;i<=nrOfNodes;i++){
    for(int j=0;j<=nrOfNodes;j++){
      if(k%2==1){
        if(i==j){
          if(firstArray[i][j]<0){
            return 1;
          }
        }


        if(firstArray[i][j]<=(firstArray[i][k]+firstArray[k][j] )){
          if(firstArray[i][j]<answerShortPath){
            cout<<"new minimum "<<firstArray[i][j]<<endl;
            answerShortPath = firstArray[i][j];
          }

          secondArray[i][j] = firstArray[i][j];

        }
        else{
          if( (firstArray[i][k]+firstArray[k][j]) <answerShortPath){
            cout<<"new minimum "<<firstArray[i][k]+firstArray[k][j] <<endl;
            answerShortPath = firstArray[i][k]+firstArray[k][j];
          }

          secondArray[i][j] = firstArray[i][k]+firstArray[k][j];
        }
        

      }
      else{

        if(i==j){
          if(secondArray[i][j]<0){
            return 1;
          }
        }



         if(secondArray[i][j]<=(secondArray[i][k]+firstArray[k][j] )){

            if(secondArray[i][j]<answerShortPath){
            cout<<"new minimum "<<secondArray[i][j]<<endl;
            answerShortPath = secondArray[i][j];
          }

          firstArray[i][j] = secondArray[i][j];

        }
        else{
           if( (secondArray[i][k]+secondArray[k][j]) <answerShortPath){
            cout<<"new minimum "<<secondArray[i][k]+secondArray[k][j]<<endl;
            answerShortPath = secondArray[i][k]+secondArray[k][j];
          }

          firstArray[i][j] = secondArray[i][k]+firstArray[k][j];
        }
      }
      
     
      
      
    }// end j
    
  }
  
} // end k

cout<<answerShortPath<<endl;
}