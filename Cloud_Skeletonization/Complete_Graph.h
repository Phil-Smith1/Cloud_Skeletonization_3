#pragma once

#include "Graph.h"

void Complete_Graph ( vector<Data_Pt>const& cloud, Graph& g )
{
    vector<Graph::vertex_descriptor> v;
    vector<pair<Graph::edge_descriptor, bool>> e;
    size_t cloud_size = cloud.size();
    
    for (int counter = 0; counter < cloud_size; ++counter)
    {
        v.push_back( boost::add_vertex( g ) );
        g[v[counter]].pt = cloud[counter].pt;
    }
    
    for (int counter_1 = 0; counter_1 < cloud_size; ++counter_1)
    {
        for (int counter_2 = counter_1 + 1; counter_2 < cloud_size; ++counter_2 )
        {
            e.push_back( boost::add_edge( counter_1, counter_2, g ) );
            Point2d source = g[boost::source( e.back().first, g )].pt;
            Point2d target = g[boost::target( e.back().first, g )].pt;
            double length = norm( target - source );
            boost::put( boost::edge_weight_t(), g, e.back().first, length );
        }
    }
}
