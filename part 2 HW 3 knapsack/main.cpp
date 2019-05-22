#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <utility>
#include <map>
using namespace std;

/*
antagligen tar denna för lång tid men vi testar
tänkte köra för 1000 columner

*/
// kanske rätt svar 2595819
// eller 4243395
int getMaxValue(int i,int j, map <pair<int,int>,int> &mapValue,  const vector <pair <int,int> > &items);
int counter = 0;

int main() {

  std::cout << "Hello World!\n";
  map <pair<int,int>,int> mapValue;

  mapValue.insert(make_pair(make_pair(0,0),0 ));
  //mapValue.insert(make_pair(make_pair(1000,1),10 ));
  //mapValue.insert(make_pair(make_pair(3,2),5 ));
  // if pair.second = 0, då är vi i första columnen
  // så ska pari.first = 0 innan vi kollar i mappen.
  // så vi slipper 200000 nollor. 1,0 2,0 --- 2000000,0
  //kanske int ens behöver mappa det? utan bara ger svaret 0?

  int weight;
  int nrOfItems;
  double tempValue;
  double tempWeight;
  double tempKvot;
  vector <int> valueVector;
  vector <int> weightVector;
  vector <pair <int,int> > items; 
  ifstream input;
	input.open("knapsack1.txt");
  input >> weight; // 
  input >> nrOfItems;
  
  if( input.fail() ){
    cout<<"filen hittades inte"<<endl;
    return 1;
  }

  cout<<"läser in tal"<<endl;
  while(!input.eof()){
    input>> tempValue;
    input>> tempWeight;
    items.push_back(make_pair(tempValue,tempWeight));
  }
 cout<< "klar med inläsning"<<endl;
int answer;
answer = getMaxValue(nrOfItems,weight,mapValue, items);
cout<<"answer "<<answer<<endl;

int currentMax = 0;
int arg_max1 = 0;
int arg_max2 =0;
for(auto it = mapValue.begin(); it != mapValue.end(); ++it ){ 
    if (it ->second > currentMax) {
        arg_max1 = it->first.first;
        arg_max2 = it->first.second;
        currentMax = it->second;
    }
}
cout <<"Största värde " << currentMax<<" finns på plats " << arg_max1<<","<<arg_max2 << endl;
 cout<<"rätt svar för knapsack1.txt: "<<2493893<<endl;
 cout<<"rätt svar för knapsack_big.txt: "<<4243395<<endl;
 //2202778
 //2493893



}

// hur får jag ut svaret? highest value in map
// https://stackoverflow.com/questions/9370945/c-help-finding-the-max-value-in-a-map
int getMaxValue(int nrOfitems,int weight, map <pair<int,int>,int> &mapValue,  const vector <pair <int,int> > &items){

int contenderOne;
int contenderTwo;

pair <int,int> tempPair;
tempPair.first = nrOfitems;
tempPair.second = weight;
map <pair<int,int>,int>::iterator it = mapValue.find(tempPair);

counter++;

if(counter%100000==0){
  cout<<counter<<endl;
}

// basecase
if(nrOfitems == 0 ){
  //cout<< "no items return 0"<<endl;
  return 0;
}

// jag vill kolla om mitt tal finns i min map

if(it != mapValue.end()){
  //hittad!
  
  return it->second;
}
else{
  // inte hittad
  // kollar ett steg till vänster i den fiktiva 2darrayn
  contenderOne = getMaxValue(nrOfitems-1 ,weight,mapValue, items);
  

  if( (weight-items[nrOfitems-1].second) > 0 ){
    contenderTwo = getMaxValue(nrOfitems-1 ,weight-items[nrOfitems-1].second, mapValue, items) + items[nrOfitems-1].first;
    
   
  }
  else{ 
    contenderTwo = contenderOne;
     
}

}

//lägger in i map
if(contenderTwo>contenderOne){
   mapValue.insert(make_pair(make_pair(nrOfitems,weight), contenderTwo ));

}
else{
  mapValue.insert(make_pair(make_pair(nrOfitems,weight),contenderOne ));
}

//cout<< "max(contenderOne,contenderTwo) "<<max(contenderOne,contenderTwo)<<endl;
return max(contenderOne,contenderTwo);



}