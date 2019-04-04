#pragma once

#include <boost/graph/connected_components.hpp>

#include "Graph.h"
#include "Cluster.h"
#include "Binary_Search_Tree.h"

void Remove_Small_Mapper_Components ( Graph& g, vector<Cluster>const& cluster, double min_comp_size )
{
    size_t num_clusters = cluster.size();
    
    vector<int> comp( num_clusters );
    
    int num_comps = boost::connected_components( g, &comp[0] ); // Assigns each vertex to its connected component.
    
    if (num_comps > 1)
    {
        vector<int> comp_size( num_comps, 0 );
        vector<vector<int>> conn_comp_vertices( num_comps );
        
        for (int counter = 0; counter < num_clusters; ++counter)
        {
            comp_size[comp[counter]] += cluster[counter].cloud.size();
            conn_comp_vertices[comp[counter]].push_back( counter );
        }
        
        bool need_to_remove = false;
        
        for (int counter = 0; counter < num_comps; ++counter)
        {
            if (comp_size[counter] < min_comp_size) need_to_remove = true;
        }
        
        if (need_to_remove)
        {
            Graph reduced_graph;
            
            for (int counter_1 = 0; counter_1 < num_comps; ++counter_1)
            {
                if (comp_size[counter_1] < min_comp_size) continue;
                
                else
                {
                    size_t num_vertices = conn_comp_vertices[counter_1].size();
                    vector<Graph::vertex_descriptor> v;
                    
                    for (int counter_2 = 0; counter_2 < num_vertices; ++counter_2)
                    {
                        v.push_back( boost::add_vertex( reduced_graph ) );
                        reduced_graph[v[counter_2]].pt = g[conn_comp_vertices[counter_1][counter_2]].pt;
                        reduced_graph[v[counter_2]].index = g[conn_comp_vertices[counter_1][counter_2]].index;
                    }
                }
            }
            
            vector<pair<Graph::edge_descriptor, bool>> e;
            Binary_Search_Tree bst;
            
            for (auto vi = boost::vertices( reduced_graph ).first; vi != boost::vertices( reduced_graph ).second; ++vi)
            {
                bst.insert( reduced_graph[*vi].index );
            }
            
            for (auto ei = boost::edges( g ).first; ei != boost::edges( g ).second; ++ei)
            {
                int s = g[boost::source( *ei, g )].index;
                
                if (bst.search( s ))
                {
                    vertex_iter vi_1, vi_2;
                    
                    for (vi_1 = boost::vertices( reduced_graph ).first; vi_1 != boost::vertices( reduced_graph ).second; ++vi_1)
                    {
                        if (reduced_graph[*vi_1].index == s) break;
                    }
                    
                    int t = g[boost::target( *ei, g )].index;
                    
                    for (vi_2 = boost::vertices( reduced_graph ).first; vi_2 != boost::vertices( reduced_graph ).second; ++vi_2)
                    {
                        if (reduced_graph[*vi_2].index == t) break;
                    }
                    
                    e.push_back( boost::add_edge( *vi_1, *vi_2, reduced_graph ) );
                    Point2d source = reduced_graph[boost::source( e.back().first, reduced_graph )].pt;
                    Point2d target = reduced_graph[boost::target( e.back().first, reduced_graph )].pt;
                    double length = norm( target - source );
                    boost::put( boost::edge_weight_t(), reduced_graph, e.back().first, length );
                }
            }
            
            g = reduced_graph;
        }
    }
}
