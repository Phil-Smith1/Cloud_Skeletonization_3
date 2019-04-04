#pragma once

#include "Data_Pt.h"

void Reduce_MST ( Graph& mst, Graph& g )
{
    multimap<double, boost::graph_traits<Graph>::edge_descriptor> edge_lengths;
    Weight weight = get( boost::edge_weight, mst );
    
    for (auto ei = edges( mst ).first; ei != edges( mst ).second; ++ei)
    {
        edge_lengths.insert( make_pair( weight[*ei], *ei ) );
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
        
        vector<Graph::vertex_descriptor> v;
        vector<pair<Graph::edge_descriptor, bool>> e;
        size_t num_vertices = boost::num_vertices( mst );
        
        for (int counter = 0; counter < num_vertices; ++counter)
        {
            v.push_back( boost::add_vertex( g ) );
            g[v[counter]].pt = mst[counter].pt;
        }
        
        for (auto it = edge_lengths.begin(); it != edge_lengths.end(); ++it)
        {
            if (it->first < cutoff)
            {
                e.push_back( boost::add_edge( source( it->second, mst ), target( it->second, mst ), g ) );
                Point2d source = g[boost::source( e.back().first, g )].pt;
                Point2d target = g[boost::target( e.back().first, g )].pt;
                double length = norm( target - source );
                boost::put( boost::edge_weight_t(), g, e.back().first, length );
            }
            
            else break;
        }
    }
}

void Reduce_MSTs ( vector<Graph>& mst, vector<Graph>& g )
{
    size_t num_intervals = mst.size();
    
    g.resize( num_intervals );
    
    for (int counter = 0; counter < num_intervals; ++counter)
    {
        Reduce_MST( mst[counter], g[counter] );
    }
}
