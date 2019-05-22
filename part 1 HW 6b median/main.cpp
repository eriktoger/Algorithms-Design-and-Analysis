#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;
/*
jag vill ha två heaps.
en max heap och en min heap.
om de blir olika stora så ska ett tal tas från den ena och läggas till den andre.

vi har en median. om talet är mindre läggs det i min lilla (max-givande) heap och om det är större så läggs det i min stora (min-givande) heap. och om det blir obalans så läggs antingen max från lilla till den stora
eller min från stora till den lilla.
nu beräknar vi medianen.
nytt tal kommer in

sedan vill jag ta ut medianen
odd är (k+1)/2 medianen
even är k/2 medianen

Jag vill alltid ta medianen från en heap (tex lilla)
2 1    3 ( här är 2 median)
2 1   3 4 (här är 2 median)
så om stora är en större
2 1   3 4 5 så ska det minsta talet skickas till lilla.
3 2 1   4 5 ( för nu är 3 median)

men lilla ser nog ut så här
 
2 1   

heap implementation details
insert and bubble up 11 min 
extract and bubble down 15 min

av  någon anledning så blir det fel efter ett tag.
mycket oklart varför.

*/


void ordnaStoraHeap(vector <int> &);
void ordnaLillaHeap(vector <int> &);

int main() {
  std::cout << "Hello World!\n";
  vector <int> storaHeap;
  vector <int> lillaHeap;
  vector <int> control;
  int newNumber;
  int runningMedian = 0;
  int controlMedian = 0;
  int currentMedian = 0;
  int temp1;
  int temp2;
  int temp3;
  int pos;
  int loopCounter = 0;

  ifstream input;
	input.open("median.txt");
   while (!input.eof()){
     input >> newNumber;
     /*
     control.push_back(newNumber);
     sort(control.begin(),control.end());
     controlMedian += control[(control.size()-1) /2];
     controlMedian = controlMedian % 10000;
     */
     // 0 1 2 3 4
     //0 1 2 3

     //cout<<"newNewnumber "<<newNumber<<endl;

     if(newNumber <= currentMedian){
       //läggs i lillaHeap;
       
       lillaHeap.push_back(newNumber);
       // här måste vi också ordna lillHeap;
       //för tänk om talet vi la in var större sin parent?
       ordnaLillaHeap(lillaHeap);
       

     }
     else{
       //läggas i stora heap;
       //cout<<"a"<<endl;
       storaHeap.push_back(newNumber);
       // här måste vi ordna storaHeap
       ordnaStoraHeap(storaHeap);
      
     }
     //cout<<"b"<<endl;

     if(lillaHeap.size() > (storaHeap.size()+1)  ){
       //cout<<"c"<<endl;
      //  om lillaheap är 3 och storaheap är 1
      // så ska ett tal från lillaHeap flyttas till
      // stora heap

      // swap första och sista talet i lillaHeap;
      
      temp1 = lillaHeap[0];
      temp2 = lillaHeap[lillaHeap.size()-1];
      lillaHeap[lillaHeap.size()-1] = temp1; //behövs ej
      lillaHeap[0] = temp2;

      //ta bort sista talet och lägger det i storaHeap.
      lillaHeap.pop_back();
      //ordnaLillaHeap(lillaHeap);

      storaHeap.push_back(temp1);
      // ordnar storaHeap;
      ordnaStoraHeap(storaHeap);


      //bubble down första talet i lillaHeap (som är en maxheap)
      pos =0;
      loopCounter =0;
      while(true){
        loopCounter++;
        if(loopCounter>100){
          cout<<"break "<<endl;
          break;
        }
        //cout<<pos<<endl;

        // först måste jag veta om det finns 0 1 eller 2 child till lillaHeap[pos];

        // if 0 children. break;
        if( ((pos+1)*2 -1) > (lillaHeap.size() -1)  ){
          //cout<<"first break"<<endl;
          break;
        }

        // if 1 children kolla om vi är störra/mindre
        if(((pos+1)*2 -1) == (lillaHeap.size() -1) ){
          temp1 = lillaHeap[pos];
          temp2 = lillaHeap[(pos+1)*2 -1];
          if(temp1<temp2){
            lillaHeap[pos] = temp2;
            lillaHeap[(pos+1)*2 -1] = temp1;
          }
          //swap
          //cout<<"second break"<<endl;
          break;

        }

        // if 2 children kolla vilken av dessa som är störst. för detta är en max heap
        if( ((pos+1)*2 -1) < (lillaHeap.size() -1) ){
          //cout<<"third variation"<<endl;
          temp1 = lillaHeap[(pos+1)*2 -1];
          temp2 = lillaHeap[(pos+1)*2];
          temp3 = lillaHeap[pos];
          
          if(temp1<=temp2){
            if(temp2>temp3){ //bytt tecken
              lillaHeap[pos] = temp2;
              lillaHeap[(pos+1)*2] = temp3;
              pos = (pos+1)*2;
            }
            else{
              break;
            }
                  
          }
          else{ // temp1> temp2
            if(temp1>temp3){ //bytt tecken
              lillaHeap[pos] = temp1;
              lillaHeap[(pos+1)*2-1] = temp3;
              pos = (pos+1)*2-1;
            }
            else{
              break;
            }

          }

        }

      } // while bubble down

      // bubble up sista talet i stora heap (som är en min heap)
      

     } // end if lillaHeap.size() > (storaHeap.size() +1)

     if(lillaHeap.size() < (storaHeap.size() ) ){
      // om storHeap är större så ska vi flytta ett tal till lillaHeap

      //swapa första och sista talet
      temp1 = storaHeap[0];
      temp2 = storaHeap[storaHeap.size()-1];
      storaHeap[storaHeap.size()-1] = temp1;
      storaHeap[0] = temp2;

      // raderar sista talet och ordnar storaheap
      storaHeap.pop_back();
      //ordnaStoraHeap(storaHeap); behövs ej
      // ordna borde heta bubble up

      // lägger in talet i lillaHeap
      lillaHeap.push_back(temp1);
      ordnaLillaHeap(lillaHeap);

      // bubble down första talet i storaHeap som är en min heap
      pos = 0;
      loopCounter =0;

      while(true){
        if(storaHeap.size()==0){
          break;
        }
        loopCounter++;
        if(loopCounter>100){
          cout<<"break"<<endl;
          break;
        }

        // först måste jag veta om det finns 0 1 2 children

        if( ((pos+1)*2 -1) > (storaHeap.size() -1)  ){
          //cout<<"first break"<<endl;
          break;
        }
         // if 1 children kolla om vi är störra/mindre
        if(((pos+1)*2 -1) == (storaHeap.size() -1) ){
          temp1 = storaHeap[pos];
          temp2 = storaHeap[(pos+1)*2 -1];
          if(temp1 > temp2){
            storaHeap[pos] = temp2;
            storaHeap[(pos+1)*2 -1] = temp1;
          }
          //swap
          //cout<<"second break"<<endl;
          break;

        }

        if( ((pos+1)*2 -1) < (storaHeap.size() -1) ){
          //cout<<"third variation"<<endl;
          temp1 = storaHeap[(pos+1)*2 -1];
          temp2 = storaHeap[(pos+1)*2];
          temp3 = storaHeap[pos];
          
          if(temp1>=temp2){
            if(temp2<temp3){
              storaHeap[pos] = temp2;
              storaHeap[(pos+1)*2] = temp3;
              pos = (pos+1)*2;
            }
            else{
              break;
            }
                  
          }
          else{ // temp1> temp2
            if(temp1<temp3){
              storaHeap[pos] = temp1;
              storaHeap[(pos+1)*2-1] = temp3;
              pos = (pos+1)*2-1;
            }
            else{
              break;
            }

          }

        }

      } // end while


     }

     // ta fram nya median
    
     currentMedian = lillaHeap[0];
     //cout<<"current Median "<<currentMedian<<", ";

     runningMedian += (currentMedian % 10000);
     runningMedian = (runningMedian % 10000);
      
     //cout<<endl<<"runningMedian "<< runningMedian<<endl<<endl;
      /*
      cout<<endl;
     cout<<"lillaHeap ";

   for(int i : lillaHeap){
     cout<<i<<", ";
   }
   cout<<endl;
   cout<<"lillaHeap.size() " <<lillaHeap.size()<<endl;

   cout<<endl;
   cout<<"storaHeap ";

   for(int i : storaHeap){
     cout<<i<<", ";
   }
   cout<<endl;
   cout<<"storaHeap.size() " <<storaHeap.size()<<endl;

   cout<< endl<<" new round"<<endl<<endl;
   */

   

   if(storaHeap.size()>0){
     if (storaHeap[0]<lillaHeap[0]){
       break;
     }
   }

   } // end while input

   cout<<endl;
   cout<<"runningMedian " <<runningMedian<<endl;
   
   cout<<endl;
   /*
   cout<<"controlMedian " <<controlMedian<<endl;
   cout<<endl;
   cout<<"lillaHeap"<<endl;
   cout<<endl;

   for(int i : lillaHeap){
     cout<<i<<", ";
   }
   cout<<endl;
   cout<<endl;

   cout<<endl;
   cout<<"storaHeap"<<endl;
   cout<<endl;

   for(int i : storaHeap){
     cout<<i<<", ";
   }
   cout<<endl;
   cout<<lillaHeap.size()<<endl;
    cout<<storaHeap.size()<<endl;
   
*/
}

void ordnaLillaHeap(vector <int> & lillaHeap){
   
   int pos = lillaHeap.size()-1;
   int temp1;
   int temp2;
   while(pos!=0){     
    if(lillaHeap[pos] > lillaHeap[ (pos-1) / 2 ] ){
      temp1 = lillaHeap[pos];
      temp2 =  lillaHeap[ (pos-1) / 2 ]; 
      lillaHeap[pos] = temp2;
      lillaHeap[ (pos-1) / 2 ] = temp1;
    }
    else{
      break;
    }
    pos=(pos-1) / 2;
    
    } // end while pos !=0
}

void ordnaStoraHeap(vector <int> &storaHeap){
int pos;
int temp1;
int temp2;
pos = storaHeap.size()-1;
       while(pos!=0){
         
        if(storaHeap[pos] < storaHeap[ (pos-1) / 2 ] ){
          temp1 = storaHeap[pos];
          temp2 =  storaHeap[ (pos-1) / 2 ]; 
          storaHeap[pos] = temp2;
          storaHeap[ (pos-1) / 2 ] = temp1;
        }
        else{
          break;
        }
        pos= (pos-1) /  2;
        
       } // end while pos !=0

}
