#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <utility>
#include <map>
#include <cmath>

using namespace std;

/*
https://www.tutorialspoint.com/design_and_analysis_of_algorithms/design_and_analysis_of_algorithms_travelling_salesman_problem.htm

mitt mål är att följa denna
*/

/*
1 läs in distans
2 skapa en table
3 ta fram minsta route
4 profit!
*/

double dist(double x1, double y1,double x2,double y2);

double pathLength(vector <int> path,int endCity, const double distTable[25][25],  map < pair<vector<int>,int>,double> &pathMap);

int main() {
  double distTable[25][25];
  int nrOfCitys;
  int CityCounter = 0;
  vector <pair<double,double> > distanceVector;
  pair <double,double> tempCoordinates;
  map < pair<vector<int>,int>,double> pathMap;
  vector <int> path;
  vector <int> tempPath;
  double answer =99999999;
  double tempAnswer;

ifstream input; 
  input.open("tsp.txt");
   if( input.fail() ){
    cout<<"filen hittades inte"<<endl;
    return 1;
  }
  else{
    cout<<"läser in tal"<<endl;
  }

  input>>nrOfCitys;
  while(!input.eof()){
    input>> tempCoordinates.first;
    input>> tempCoordinates.second;
    distanceVector.push_back(tempCoordinates);
  }
  
  cout<<"skapar table och path"<<endl;
  for(int i=0;i<distanceVector.size();i++){
    path.push_back(i);
    for(int j=0;j<distanceVector.size();j++){
      distTable[i][j] = dist(distanceVector[i].first,distanceVector[i].second, distanceVector[j].first, distanceVector[j].second );
    }
  }
  cout<<endl;
  for(int i=1;i<nrOfCitys;i++){
    // är verkligen detta korrekt?
    // det blir fel i alla fall.
    // kolla hemsidan noggrannare om
    cout<<i<<endl;
    tempPath = path;
    //cout<<"b"<<endl;
    //tempPath.erase(tempPath.begin()+i);
    //cout<<"c"<<endl;
    tempAnswer= pathLength(tempPath,i,distTable,pathMap);
    //cout<<"d"<<endl;
    tempAnswer+=distTable[i][0];
    //cout<<"e"<<endl;
    //cout<<tempAnswer<<endl;
    answer= min(answer,tempAnswer);
  }

cout<<"mitt svar för "<< nrOfCitys<<" "<< answer<<endl;
// skulle kunna lägga in dem i en array.
cout<< "svar för 5 "<<8387.09<<endl;
cout<< "svar för 6 "<<8607.43<<endl; 
cout<< "svar för 7 "<<9498.2<<endl;
cout<<"svar för 8 " <<9765.2<<endl;
cout<<"svar för 9 " <<10769.2<<endl;
cout<<"svar för 10 " <<12350<<endl;
cout<<"svar för 11 " <<12518<<endl;
cout<<"svar för 16 " <<22943.2<<endl;
cout<<"svar för 17 " <<22953.6<<endl;
cout<<"svar för 25 "<<26442<<endl;
}

double dist(double x1, double y1,double x2,double y2){

  return sqrt( pow( x1-x2,2)+pow(y1-y2,2) );
}

double pathLength(vector <int> path,int endCity, const  double distTable[25][25],map < pair<vector<int>,int>,double> &pathMap ){
 

  double answer = 999999.0;
  double tempAnswer;
  vector <int> shortPath;
  vector <int>::iterator it;
  int newEndCity=-1;
  
  //ändrade båda dessa till ==2
  // för det ska väl alltid finnas två?
  //jag tror inte denna behövs för att endCity är aldrig 0
  if(path.size()==2 & endCity==0){
    //cout<<"zero"<<endl;
    return 99999999;
  }
  
  //cout<<"pl2"<<endl;
  if(path.size()==2 & endCity!=0 ){
    //cout<<"bottom"<<endl;
    return distTable[endCity][0];
  }
  shortPath = path;
  
  shortPath.erase(std::remove(shortPath.begin(), shortPath.end(), endCity), shortPath.end());


  // kollar om shortPath redan är beräknad
  for(int i=1;i<shortPath.size();i++){
    if(pathMap.find(make_pair(shortPath,shortPath[i])) !=pathMap.end()){
    
      tempAnswer = pathMap.find(make_pair(shortPath,shortPath[i]))->second;
    
    }
    else{
      // här beräknas shortPath
      tempAnswer=pathLength(shortPath,shortPath[i],distTable,pathMap); 
    }
    // lägger till sista avståndet
    tempAnswer+= distTable[endCity][shortPath[i]];
    
    // kan tas bort
    if(tempAnswer<answer){
      newEndCity =shortPath[i];
    }

    //sparar minimum
    answer=min(answer,tempAnswer);
  }
  

  /*
  innan lade jag in det som står under. Men det var ju intes svaret. Men jag vill bara försäkra mig om att detta är rätt
  */
   pathMap.insert(make_pair(make_pair(path,endCity),answer ));
    //pathMap.insert(make_pair(make_pair(shortPath,newEndCity),answer ));
  
  return answer;
}