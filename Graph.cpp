//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Graph.h"

using namespace std;

Graph::Graph(string label)
{
	numE = 0;
	V = label;
}
		
void Graph::setEdges(const	uint* pairs, uint size)
{
	numE = size >> 1;
	
	for(uint i = 0; i < size; i+= 2)
	{
		uint p[2] = {pairs[i], pairs[i+1]};
		
		E.push_back(p);
	}
}		
		
void Graph::Print(void)
{
	cout << "G([" << V << "], {";
	
	for(uint i = 0; i < E.size(); i++)
	{
		cout << "{" << E[i][0] << ", " << E[i][1] << "}";		
				
		if(i < E.size() - 1)
		{
			cout << ", ";
		}
	}
		
	cout << "})" << endl;
}