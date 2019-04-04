#pragma once

#include "Recover_Components.h"

void Generate_Subgraphs ( Graph const& g, vector<vector<Data_Pt>>const& subcloud, vector<Graph>& subgraph )
{
	size_t num_subclouds = subcloud.size();
    
    subgraph.resize( num_subclouds );

	for (int counter = 0; counter < num_subclouds; ++counter)
	{
        Recover_Components( g, subcloud[counter], subgraph[counter] );
	}
}
