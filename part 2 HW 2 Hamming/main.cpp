#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <utility>
#include <map>
using namespace std;

// https://github.com/dbarabanov/coursera/blob/master/algorithms_2/assignment_2/question_2.py

// https://lagunita.stanford.edu/courses/course-v1:Engineering+Algorithms2+SelfPaced/discussion/forum/Engineering-Algorithms2-course-SelfPaced_programming-assignments/threads/59ca72195e5647a0340058a6

/*
Vad vill jag göra?

kanske ska börja med 200000 kluster?


lägg in alla strings i vektor
lägg all i en map. Map är string(namn) leader (sig själv?)

gå igenom vektor med for loop
 gå igenom alla varianter med två skillnader.
 glöm inte kolla en skillnad också
 kolla om varianten finns i map. finns den det så kolla leader. om leader1 != leader2 så ska de joinas.
 och clusters--.

svaret kommer vara hur många clusters det finns kvar.

*/
string findBoss(map<string,string> &distanceMap, string nrDisString);

int main() {
  vector <string> distanceVector;
  map <string,string> distanceMap;
  int antalNodes;
  int antalBits;
  string distanceString;
  int counter = 0;
  map<string, string>::iterator it = distanceMap.begin();
  map<string, string>::iterator itDis0;
  map<string, string>::iterator itDis1;
  map<string, string>::iterator itDis2;

  ifstream input;
	input.open("clustering_big.txt");
  input >> antalNodes; 
  input >> antalBits;
  if( input.fail() ){
    cout<<"filen hittades inte"<<endl;
    return -1;
  }
  getline(input,distanceString); // äter upp första raden
  while(!input.eof()){
    getline(input,distanceString);
    distanceVector.push_back(distanceString);
    distanceMap.insert(make_pair( distanceString,distanceString) );
    counter++;
    
  }
  cout<< "klar med inläsning: "<<counter<<" "<<distanceMap.size() <<endl;

  
  /*
  hur map fungerar

  it = distanceMap.find("1 0 1 0 1 0 1 1 1 1 0 1 1 0 0 0 1 1 0 1 0 0 0 1 "); // obs mellanslag på slutet
  cout<<"hej"<<endl;
  distanceMap["1 0 1 0 1 0 1 1 1 1 0 1 1 0 0 0 1 1 0 1 0 0 0 1 "] ="hejsan";
  if(it!=distanceMap.end()){
    cout<<it-> first<<endl;
    cout<<it-> second<<endl;
  }
  else{
    cout<<"hittades ej"<<endl;
  }
  */

  cout<<"nu börjar vi reducera cluster!"<<endl;

  string zeroDisString;
  string oneDisString;
  string twoDisString;
  int foundCounter = 0;
  string boss1;
  string boss2;
  int antalCluster = 0;
  int limit =1;

  vector <string> tempVector;
  string tempFirst;
  cout<<"distanceMap.size() "<<distanceMap.size()<<endl;
  // storleketen i mitt första cluster är lite för stor
   // 191880 fastän alla andra är singlar så blir det inte ca 16000 st
  
  while(distanceMap.size()>0){
    tempVector.clear();
    tempFirst = (distanceMap.begin()->first);
    tempVector.push_back(tempFirst);
    distanceMap.erase(tempFirst);
    antalNodes--;
    if(antalNodes%1000 ==0){
      cout<<antalNodes<<endl;
    }
  
    antalCluster++;
    //cout<<antalCluster<<endl;
    
    for(int i=0;i<tempVector.size();i++){

      zeroDisString = tempVector[i];
      if (tempVector.size()>  limit ){
        cout<<tempVector.size()<<endl;
        limit*=2;
      }

      for(int j=-2;j< (int) zeroDisString.size();j=j+2){
        oneDisString = zeroDisString;
       
        if(j != -2){
          if (zeroDisString[j]=='1'){
            oneDisString[j] ='0';
          }
          else{
            oneDisString[j] ='1';
          }
        }

        // om vi hittar en så läggs den till i tempVector
        if(distanceMap.find(oneDisString) != distanceMap.end() ){
          tempVector.push_back(oneDisString);
          distanceMap.erase(oneDisString);
        }

        twoDisString = oneDisString;
        for(int k=-2;k< (int) oneDisString.size();k=k+2){
          twoDisString = oneDisString;
          
          if(k !=-2){
            if (oneDisString[k]=='1'){
            twoDisString[k] ='0';
            }
            else{
              twoDisString[k] ='1';
            }
          }

          if(distanceMap.find(twoDisString)!=distanceMap.end() ){
          tempVector.push_back(twoDisString);
          distanceMap.erase(twoDisString);
    
        }


         }//en for k



      } // end for j
      


    } // end for i

    
  }

cout<<"antalCluster " <<antalCluster<<endl;

}
