#pragma once

#include "Graph_H.h"

bool Collapse_Shortest_Edge ( Graph_H& hopes_graph, double crit_length )
{
    if (hopes_graph.vertices.size() <= 2) return false;
    
    int edge = 0;
    double min_length = 1e+8;
    
    for (int counter = 1; counter < hopes_graph.edges.size(); ++counter)
    {
        double length = sqrt( squared_distance( hopes_graph.vertices[hopes_graph.edges[counter].first], hopes_graph.vertices[hopes_graph.edges[counter].second] ) );
        
        if (length < min_length && length != 0)
        {
            min_length = length;
            edge = counter;
        }
    }
    
    if (min_length > crit_length) return false;
    
    int v1 = hopes_graph.edges[edge].first, v2 = hopes_graph.edges[edge].second;
    double x,y;
    
    if ((hopes_graph.wedges[v1].size() == 2 && hopes_graph.wedges[v2].size() == 2) || (hopes_graph.wedges[v1].size() != 2 && hopes_graph.wedges[v2].size() != 2))
    {
        x = 0.5 * (hopes_graph.vertices[v1].x() + hopes_graph.vertices[v2].x());
        y = 0.5 * (hopes_graph.vertices[v1].y() + hopes_graph.vertices[v2].y());
    }
    
    else if (hopes_graph.wedges[v1].size() != 2)
    {
        x = hopes_graph.vertices[v1].x();
        y = hopes_graph.vertices[v1].y();
    }
    
    else
    {
        x = hopes_graph.vertices[v2].x();
        y = hopes_graph.vertices[v2].y();
    }
    
    P2 v( x, y );
    
    hopes_graph.vertices[v1] = v;
    
    int v1_wedge = 0, v2_wedge = 0;
    
    for (; v1_wedge < hopes_graph.wedges[v1].size(); ++v1_wedge) if (hopes_graph.wedges[v1][v1_wedge] == edge) break;
    
    hopes_graph.wedges[v1].erase( hopes_graph.wedges[v1].begin() + v1_wedge );
    
    for (int counter = 0; counter < hopes_graph.wedges[v2].size(); ++counter)
    {
        if (hopes_graph.wedges[v2][counter] == edge) v2_wedge = counter; // old edge from v2 to v1
        
        else
        {
            hopes_graph.wedges[v1].push_back( hopes_graph.wedges[v2][counter] );
            
            if (hopes_graph.edges[hopes_graph.wedges[v2][counter]].first == v2) hopes_graph.edges[hopes_graph.wedges[v2][counter]].first = v1;
            
            else hopes_graph.edges[hopes_graph.wedges[v2][counter]].second = v1;
        }
    }
    
    hopes_graph.vertices.erase( hopes_graph.vertices.begin() + v2 );
    hopes_graph.wedges.erase( hopes_graph.wedges.begin() + v2 );
    hopes_graph.edges.erase( hopes_graph.edges.begin() + edge );
    hopes_graph.edgelengths.erase( hopes_graph.edgelengths.begin() + edge );
    
    for (int counter = 0; counter < hopes_graph.edges.size(); ++counter)
    {
        if (hopes_graph.edges[counter].first > v2) --hopes_graph.edges[counter].first;
        if (hopes_graph.edges[counter].second > v2) --hopes_graph.edges[counter].second;
    }
    
    for (int counter_1 = 0; counter_1 < hopes_graph.wedges.size(); ++counter_1)
    {
        for (int counter_2 = 0; counter_2 < hopes_graph.wedges[counter_1].size(); ++counter_2)
        {
            if (hopes_graph.wedges[counter_1][counter_2] > edge) --hopes_graph.wedges[counter_1][counter_2];
        }
    }
    
    for (int counter = 0; counter < hopes_graph.wedges[v1].size(); ++counter)
    {
        int wedge = hopes_graph.wedges[v1][counter], ver1 = hopes_graph.edges[wedge].first, ver2 = hopes_graph.edges[wedge].second;
        hopes_graph.edgelengths[wedge] = sqrt( squared_distance( hopes_graph.vertices[ver1], hopes_graph.vertices[ver2] ) );
    }
    
    return true;
}

void Simplify_HoPeS ( Graph_H& hopes_graph, double noise )
{
    while (Collapse_Shortest_Edge( hopes_graph, noise ));
}
