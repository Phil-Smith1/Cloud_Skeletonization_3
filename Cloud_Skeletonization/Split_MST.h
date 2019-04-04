#pragma once

#include "Data_Pt.h"

void Reduce_MST ( vector<vector<Data_Pt>>const& cloud, vector<Graph>& mst, vector<Graph>& g )
{
    size_t num_intervals = mst.size();
    multimap<double, pair<int, boost::graph_traits<Graph>::edge_descriptor>> edge_lengths;
    
    for (int counter = 0; counter < num_intervals; ++counter)
    {
        Weight weight = get( boost::edge_weight, mst[counter] );
        EdgePair edgepair;
        
        for (edgepair = edges( mst[counter] ); edgepair.first != edgepair.second; ++edgepair.first)
        {
            edge_lengths.insert( make_pair( weight[*edgepair.first], make_pair( counter, *edgepair.first ) ) );
        }
    }
    
    double cutoff = 0, largest_gap = 0;
    
    if (edge_lengths.size() > 0) // Removes case of MST consisting of no edges.
    {
        for (auto iter_1 = edge_lengths.begin(); iter_1 != (--edge_lengths.end()); ++iter_1)
        {
            auto iter_2 = iter_1;
            ++iter_2;
            
            double gap = iter_2->first - iter_1->first;
            
            if (gap > largest_gap)
            {
                largest_gap = gap;
                cutoff = iter_2->first;
            }
        }
    }
    
    for (int counter_1 = 0; counter_1 < num_intervals; ++counter_1)
    {
        size_t cloud_size = cloud[counter_1].size();
        vector<Graph::vertex_descriptor> v;
        v.clear();
        
        for (int counter_2 = 0; counter_2 < cloud_size; ++counter_2)
        {
            v.push_back( boost::add_vertex( g[counter_1] ) );
            g[counter_1][v[counter_2]].pt = cloud[counter_1][counter_2].pt;
        }
    }
        
    int num_edges = 0;
    vector<pair<Graph::edge_descriptor, bool>> e;
    e.clear();
    
    for (auto it = edge_lengths.begin(); it != edge_lengths.end(); ++it)
    {
        if (it->first < cutoff)
        {
            e.push_back( boost::add_edge( source( it->second.second, mst[it->second.first] ), target( it->second.second, mst[it->second.first] ), g[it->second.first] ) );
            Point2d source = g[it->second.first][boost::source( e[num_edges].first, g[it->second.first] )].pt;
            Point2d target = g[it->second.first][boost::target( e[num_edges].first, g[it->second.first] )].pt;
            double length = norm( target - source );
            boost::put( boost::edge_weight_t(), g[it->second.first], e[num_edges].first, length );
            ++num_edges;
        }
    }
}
