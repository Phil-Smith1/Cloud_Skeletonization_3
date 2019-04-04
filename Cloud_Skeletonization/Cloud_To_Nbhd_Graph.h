#pragma once

#include "Data_Pt.h"

void Cloud_To_Nbhd_Graph ( vector<Data_Pt>const& cloud, double epsilon, Graph& nbhd_graph )
{
    vector<Graph::vertex_descriptor> v;
    vector<pair<Graph::edge_descriptor, bool>> e;
    
	size_t cloud_size = cloud.size();

	for (int counter = 0; counter < cloud_size; ++counter)
	{
		v.push_back( boost::add_vertex( nbhd_graph ) );
		nbhd_graph[v[counter]].pt = cloud[counter].pt;
        nbhd_graph[v[counter]].index = cloud[counter].index;
	}

	for (int iter_1 = 0; iter_1 < cloud_size; ++iter_1)
	{
		for (int iter_2 = iter_1 + 1; iter_2 < cloud_size; ++iter_2)
		{
			double dist = norm( cloud[iter_2].pt - cloud[iter_1].pt );

			if (dist < epsilon)
			{
				e.push_back( boost::add_edge( iter_1, iter_2, nbhd_graph ) );
                boost::put( boost::edge_weight_t(), nbhd_graph, e.back().first, dist );
			}
		}
	}
}
