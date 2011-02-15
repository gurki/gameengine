//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#ifndef _GRAPH_H
#define _GRAPH_H

#include "Types.h"

#include <iostream>
#include <string>
#include <vector>

class Graph
{
	public:
	
	// constructors
	
		Graph(std::string label);
		
	// setter
	
		void setEdges(const	uint* pairs, uint size);
		
	// output
	
		void Print(void);
		
	protected:
	
		uint numV;
		uint numE;
		
		std::string V;
		std::vector<uint*> E;
};

#endif
