#pragma once

#include "Cluster.h"
#include "Binary_Search_Tree.h"

void Connect_Clusters ( vector<Cluster>const& cluster, Graph& g )
{
	vector<Graph::vertex_descriptor> v;
	vector<pair<Graph::edge_descriptor, bool>> e;
    size_t num_clusters = cluster.size();

	for (int counter = 0; counter < num_clusters; ++counter)
	{
		v.push_back( boost::add_vertex( g ) );
		g[v[counter]].pt = cluster[counter].pt;
        g[v[counter]].interval = cluster[counter].interval;
        g[v[counter]].index = counter;
	}

	for (int counter_1 = 0; counter_1 < num_clusters; ++counter_1)
	{
		for (int counter_2 = counter_1 + 1; counter_2 < num_clusters; ++counter_2)
		{
			if (cluster[counter_2].interval != cluster[counter_1].interval + 1 && cluster[counter_2].interval != cluster[counter_1].interval - 1) continue;

			else
			{
                size_t cluster_size_1 = cluster[counter_1].cloud.size();
                size_t cluster_size_2 = cluster[counter_2].cloud.size();
                Binary_Search_Tree bst;
                
                for (int counter_3 = 0; counter_3 < cluster_size_2; ++counter_3)
                {
                    bst.insert( cluster[counter_2].cloud[counter_3].index );
                }
                
                for (int counter_3 = 0; counter_3 < cluster_size_1; ++counter_3)
                {
                    if (bst.search( cluster[counter_1].cloud[counter_3].index ) != NULL)
                    {
                        e.push_back( boost::add_edge( v[counter_1], v[counter_2], g ) );
                        Point2d source = g[boost::source( e.back().first, g )].pt;
                        Point2d target = g[boost::target( e.back().first, g )].pt;
                        double length = norm( target - source );
                        boost::put( boost::edge_weight_t(), g, e.back().first, length );
                        
                        break;
                    }
                }
			}
		}		
	}
}
