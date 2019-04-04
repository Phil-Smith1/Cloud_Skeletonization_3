#pragma once

#include <boost/graph/connected_components.hpp>

#include "Cluster.h"
#include "Geometric_Centre_Of_Cloud.h"

void Grouping ( Graph const& g, vector<Data_Pt>const& cloud, int subgraph_iter, vector<Cluster>& cluster )
{
	size_t num_vertices = boost::num_vertices( g );

    vector<int> comp( num_vertices );
    
    int num_comps = boost::connected_components( g, &comp[0] );

    vector<vector<Data_Pt>> list( num_comps );

    for (int counter = 0; counter < num_vertices; ++counter)
    {
        list[comp[counter]].push_back( cloud[counter] );
    }

    for (int counter = 0; counter < num_comps; ++counter)
    {
        cluster.push_back( Cluster( list[counter], Geometric_Centre_Of_Cloud( list[counter] ), subgraph_iter ) );
    }
}

void Group_Subgraphs ( vector<Graph>const& subgraph, vector<vector<Data_Pt>>const& subcloud, vector<Cluster>& cluster  )
{
	size_t num_subgraphs = subgraph.size();

	for (int subgraph_iter = 0; subgraph_iter < num_subgraphs; ++subgraph_iter)
	{
		if (boost::num_vertices( subgraph[subgraph_iter] ) == 0) continue;

		Grouping( subgraph[subgraph_iter], subcloud[subgraph_iter], subgraph_iter, cluster );
	}
}
