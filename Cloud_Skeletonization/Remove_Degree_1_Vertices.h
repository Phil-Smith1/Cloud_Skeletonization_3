#pragma once

#include "Graph.h"
#include "Graph_H.h"

void Remove_Degree_1_Vertices( Graph& g )
{
    bool simplify = true;
    size_t num_vertices = boost::num_vertices( g );
    vector<double> depth( num_vertices, 0 );
    
    while (simplify)
    {
        simplify = false;
        
        for (int v1 = 0; v1 < num_vertices; ++v1)
        {
            if (boost::degree( v1, g ) == 1)
            {
                simplify = true;
                
                int v2;
                auto edge = boost::out_edges( v1, g ).first;
                
                if (boost::source( *edge, g ) == v1) v2 = (int)boost::target( *edge, g );
                
                else v2 = (int)boost::source( *edge, g );
                
                double d = depth[v1] + get( boost::edge_weight_t(), g, *edge );
                
                if (d > depth[v2]) depth[v2] = d;
                
                boost::remove_edge( *edge, g );
                
                boost::remove_vertex( v1, g );
            }
        }
    }
}

void Remove_Degree_1_Vertices ( Graph_H& hopes_graph )
{
    bool simplify = true;
    size_t num_vertices = hopes_graph.vertices.size();
    hopes_graph.depth.resize( num_vertices, 0 );
    
    while (simplify)
    {
        simplify = false;
        
        for (int v1 = 0; v1 < num_vertices; ++v1)
        {
            if (hopes_graph.wedges[v1].size() == 1)
            {
                simplify = true;
                
                int v2, edge = hopes_graph.wedges[v1][0];
                
                if (hopes_graph.edges[edge].first == v1) v2 = hopes_graph.edges[edge].second;
                
                else v2 = hopes_graph.edges[edge].first;
                
                double depth = hopes_graph.depth[v1] + hopes_graph.edgelengths[edge];
                
                if (depth > hopes_graph.depth[v2]) hopes_graph.depth[v2] = depth;
                
                int w = 0;
                
                for (; w < hopes_graph.wedges[v2].size(); ++w)
                {
                    if (hopes_graph.wedges[v2][w] == edge) break;
                }
                
                hopes_graph.wedges[v2].erase( hopes_graph.wedges[v2].begin() + w );
                hopes_graph.vertices.erase( hopes_graph.vertices.begin() + v1 );
                hopes_graph.wedges.erase( hopes_graph.wedges.begin() + v1 );
                hopes_graph.edges.erase( hopes_graph.edges.begin() + edge );
                hopes_graph.edgelengths.erase( hopes_graph.edgelengths.begin() + edge );
                
                for (int counter = 0; counter < hopes_graph.edges.size(); ++counter)
                {
                    if (hopes_graph.edges[counter].first > v1) --hopes_graph.edges[counter].first;
                    if (hopes_graph.edges[counter].second > v1) --hopes_graph.edges[counter].second;
                }
                
                for (int counter_1 = 0; counter_1 < hopes_graph.wedges.size(); ++counter_1)
                {
                    for (int counter_2 = 0; counter_2 < hopes_graph.wedges[counter_1].size(); ++counter_2)
                    {
                        if (hopes_graph.wedges[counter_1][counter_2] > edge) --hopes_graph.wedges[counter_1][counter_2];
                    }
                }
            }
        }
    }
}
