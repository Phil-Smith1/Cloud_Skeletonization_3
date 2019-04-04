#pragma once

#include <boost/graph/kruskal_min_spanning_tree.hpp>

#include "Graph.h"

void MST ( Graph const& g, Graph& mst )
{
    vector<boost::graph_traits<Graph>::edge_descriptor> spanning_tree;
    
    boost::kruskal_minimum_spanning_tree( g, back_inserter( spanning_tree ) );
    
    vector<Graph::vertex_descriptor> v;
    vector<pair<Graph::edge_descriptor, bool>> e;
    size_t num_vertices = boost::num_vertices( g );
    
    for (int counter = 0; counter < num_vertices; ++counter)
    {
        v.push_back( boost::add_vertex( mst ) );
        mst[v[counter]].pt = g[counter].pt;
    }
    
    for (auto it = spanning_tree.begin(); it != spanning_tree.end(); ++it)
    {
        e.push_back( boost::add_edge( source( *it, g ), target( *it, g ), mst ) );
        Point2d source = g[boost::source( e.back().first, g )].pt;
        Point2d target = g[boost::target( e.back().first, g )].pt;
        double length = norm( target - source );
        boost::put( boost::edge_weight_t(), mst, e.back().first, length );
    }
}
