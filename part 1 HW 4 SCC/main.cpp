#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h> 

using namespace std;

/*
Jag vill ha en klass Node.
Jag vill lägga in alla nodes  Detta görs genom att kolla när radens första tal förändras. 
om den inte förändras (eller är ny) så ska vi lägga till en edge.

sedan efter det så ska vi reverse det hela?
Ska vi då gå ingeom hela filen igen och leta upp noden och lägga till utgående?
t.ex 1 5 så läggs 5 till hos 1.
Men vi vill ha 1 hos fem också.
Då måste vi hitta 5 i vår lista av nodes (och den verkar inte var på plats 5 eller 5-1) för 4 fanns inte.
Men man kanske bara ska ha sin plats och så lägger vi en en tom nodes på den platsen eller något.


http://andrew-exercise.blogspot.com/2015/11/algorithms-design-and-analysis-part-1_68.html

använder sig av två vectorer (av vectorer) och fyller på dem allt eftersom. Det verkar ju smidigt.
Men man hade ju kunnat göra samma sam med nodes.
Att när man ser en node så lägger man till något i den.


https://www.geeksforgeeks.org/strongly-connected-components/
använder sig av graph/node class

https://ideone.com/fork/f2xnzh
lösning och facit
Answer: 434821 968 459 313 211


Denna uppgift kommer nog ta ett tag
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>
#include <map>
#include <cstdlib>
#include <algorithm>
using namespace std;

void DFSRev(int node,vector<bool> &visited, vector<vector<int> > rev_graph, stack<int> &finished);

void DFSFwd(int node,vector <bool> &visited, vector<vector<int> > raw_graph, vector<vector<int> > &scc );

void stackPeep(stack <int> finished);

int main()
{

vector<vector<int> > raw_graph;
vector<vector<int> > rev_graph;
vector<bool> visited;
stack<int> finished;
vector<vector<int> > scc;

  cout << "start" << endl;
	ifstream input;
	input.open("test.txt");
	//string line;
	int counter = 0;
  int from;
	int to;

	int numNodes = 20;

	raw_graph.resize(numNodes);
	rev_graph.resize(numNodes);
	visited.resize(numNodes);


	while (!input.eof())
	{
		counter++;
		if (counter % 5 == 0) {
			cout << "counter is " << counter << endl;
		}
		
		input >> from >> to;

    // vi låssas att vi har från 0 till (n-1)
    // istället för 1-n 
		raw_graph[from - 1].push_back(to - 1);
		rev_graph[to - 1].push_back(from - 1);
	}
	input.close();
	cout << "read is done" << endl;
  
  cout<<"vanlig graf"<<endl;
  for(int i=0; i< raw_graph.size();i++){
    cout << i+1<< " ";
    for(int j=0;j<raw_graph[i].size();j++){
      cout << raw_graph[i][j]+1<< " ";
      //+1 är för vi arbetar med index
    }
    cout<<endl;

  }
  cout<<endl;
  cout<<"omvänd"<<endl;
  for(int i=0; i< rev_graph.size();i++){
    cout << i+1<< " ";
    for(int j=0;j<rev_graph[i].size();j++){
      cout << rev_graph[i][j]+1<< " ";
      //+1 är för vi arbetar med index
    }
    cout<<endl;

  }


//sätter alla visited till false.
for (int i = 0; i < numNodes; i++){
		visited[i] = false;
	}

// nu ska vi gå igenom rev_graph

for (int i = 0; i < numNodes; i++)
	{
		if (!visited[i])
		{
			DFSRev(i, visited,rev_graph,finished);
		}
	}

  stackPeep(finished);


//nollställer visited
for (int i = 0; i < numNodes; i++)
	{
		visited[i] = false;
	}


  	while (finished.size() > 0)
	{
		int candidate = finished.top();
		finished.pop();
		if (!visited[candidate])
		{
			scc.push_back( vector<int>() );
			DFSFwd(candidate,visited, raw_graph,scc);
		}
	}

  vector <int> fiveBiggest;
	fiveBiggest.push_back(0);
	fiveBiggest.push_back(0);
	fiveBiggest.push_back(0);
	fiveBiggest.push_back(0);
	fiveBiggest.push_back(0);
	fiveBiggest.push_back(0);
	
	cout << "step 2 is done" << endl;
	for (unsigned int i = 0; i < scc.size(); i++)
	{
		if (scc[i].size() > fiveBiggest[1]) {
			fiveBiggest[0] = scc[i].size();
			sort(fiveBiggest.begin(), fiveBiggest.end());

		}
	}
	cout << "biggest " << fiveBiggest[5] << " " << fiveBiggest[4] << " " << fiveBiggest[3]<< " " << fiveBiggest[2] <<" " << fiveBiggest[1] << endl;

	return 0;
}

void DFSRev(int node,vector<bool> &visited,vector<vector<int> > rev_graph, stack<int> &finished)
{
	visited[node] = true;
	for (unsigned int i = 0; i < rev_graph[node].size(); i++)
	{
		int neighbor = rev_graph[node][i];
		if (!visited[neighbor])
		{
			DFSRev(neighbor, visited,rev_graph,finished);
		}
	}
	finished.push(node);
}

void DFSFwd(int node,vector <bool> &visited, vector<vector<int> > raw_graph, vector<vector<int> > &scc )
{
	scc[scc.size() - 1].push_back(node);
	visited[node] = true;
	for (unsigned int i = 0; i < raw_graph[node].size(); i++)
	{
		int neighbor = raw_graph[node][i];
		if (!visited[neighbor])
		{
			DFSFwd(neighbor, visited,  raw_graph,scc);
		}
	}
}

void stackPeep(stack <int> finished){
  int temp;
  while(finished.size()>0){
    temp = finished.top();
    finished.pop();
    cout<<temp<< " ";
  }
  cout<<endl;
}