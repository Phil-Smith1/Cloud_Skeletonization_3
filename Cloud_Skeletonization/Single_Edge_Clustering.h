#pragma once

#include "Filtration.h"

bool IncreasingLengths ( Edge const& e1, Edge const& e2 )
{
    return e2.length > e1.length;
}

int Root ( int node, vector<int>const& uplinks )
{
    int next = uplinks[node];
    if (next == node) return node;
    return Root( next, uplinks );
}

void Single_Edge_Clustering ( double gap, vector<vector<P2>>& clouds )
{
    vector<P2> cloud = clouds[0];
    
    Filtration filtration( cloud ); // Edges and faces are found.
    
    if (filtration.delaunay.number_of_faces() != 0)
    {
        vector<int> uplinks;
        
        for (int i = 0; i < filtration.delaunay.number_of_vertices(); ++i) uplinks.push_back( i );
        
        sort( filtration.edges.begin(), filtration.edges.end(), IncreasingLengths );
        
        for (int ind_edge = 0; ind_edge < filtration.edges.size(); ++ind_edge)
        {
            Edge * edge = &filtration.edges[ind_edge];
            
            if (edge->length > gap) break;
            
            int node_u = edge->end1->info();
            int node_v = edge->end2->info();
            int root_u = Root( node_u, uplinks );
            int root_v = Root( node_v, uplinks );
            uplinks[node_u] = root_u;
            uplinks[node_v] = root_v;
            
            if (root_u == root_v) continue; // Already connected.
            
            uplinks[root_u] = root_v;
            uplinks[node_u] = root_v;
        }
        
        vector<int> indices = uplinks;
        clouds.clear();
        int num_components = 0;
        
        for (auto v = filtration.delaunay.vertices_begin(); v != filtration.delaunay.vertices_end(); ++v)
        {
            uplinks[v->info()] = Root( v->info(), uplinks ); // Final root  determines a component.
            
            int ind = -1, i = 0;
            
            for (; i < v->info(); ++i)
            {
                if (uplinks[v->info()] == uplinks[i]) // i and v are in the same component.
                {
                    ind = indices[uplinks[i]];
                    break;
                }
            }
            
            if (ind < 0)
            {
                ind = num_components++; // New component.
                clouds.push_back( vector<P2>{} ); // Empty cloud.
            }
            
            indices[uplinks[v->info()]] = ind;
            clouds[ind].push_back( v->point() );
        }
    }
}
