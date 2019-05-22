#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;

// http://andrew-exercise.blogspot.com/2015/11/algorithms-design-and-analysis-part-1_69.html
// 1000 första talen gav svaret 9 (det gav min också!)
// rätt svar är 427 (vi får se jag får samma svar!)


int main() {

  long int newNumber;
  ifstream input;
	input.open("2sum.txt");
  unordered_map <long int,long int> test;
  long int first;
  long int second;
  long int differenceY; // x+y=t  y=t-x
  int tCounter = 0;
  unordered_map <long int,long int>::iterator it;

   while (!input.eof()){

     input >> newNumber;
     if(test.count(newNumber)== 0 ){
       test.insert({newNumber,newNumber});
     }

  }

  for(int t=-10000;t<=10000;t++){
     cout<<t<<endl;

    for(it = test.begin();it != test.end();it++ ){
      first = it->first;
      differenceY = t-first;
      if( (test.count(differenceY) == 1) & ( first < differenceY ) ) {
        //cout<<"x " <<" + "<<"y"<<" = "<< t<<endl;
        //cout<<first<<" + "<<differenceY <<" = "<<t<<endl;
        tCounter++;
      }
    }
   
  }

  cout<<tCounter<<endl;
  
 

}