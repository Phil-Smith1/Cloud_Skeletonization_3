#pragma once

#include <boost/graph/connected_components.hpp>

#include "Recover_Components.h"

void Split_Into_Conn_Comps ( Graph const& g, int& num_comps, vector<vector<Data_Pt>>& conn_comp_cloud, vector<Graph>& conn_comp )
{
	size_t num_vertices = boost::num_vertices( g );
	vector<int> comp( num_vertices );
    
	num_comps = boost::connected_components( g, &comp[0] ); // Assigns each vertex to its connected component.
	
    conn_comp_cloud.resize( num_comps );
	conn_comp.resize( num_comps );
    
    for (auto vi = boost::vertices( g ).first; vi != boost::vertices( g ).second; ++vi)
    {
        Data_Pt data_pt( g[*vi].pt );
        data_pt.index = g[*vi].index;
        conn_comp_cloud[comp[data_pt.index]].push_back( data_pt );
    }
    
    if (num_comps == 1) conn_comp[0] = g;

    else
    {
        for (int counter = 0; counter < num_comps; ++counter)
        {
            Recover_Components( g, conn_comp_cloud[counter], conn_comp[counter] ); // Assigns an edge between two vertices in each component if an edge exists in the input graph.
        }
    }
}
