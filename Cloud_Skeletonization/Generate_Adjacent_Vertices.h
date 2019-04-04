#pragma once

#include "Graph.h"

void Generate_Adjacent_Vertices ( Graph const& g, vector<pair<int, vector<int>>>& adjacent_vertices )
{
    for (auto vi = boost::vertices( g ).first; vi != boost::vertices( g ).second; ++vi)
    {
        adjacent_vertices[*vi].first = (int)*vi;
        
        for (auto av = boost::adjacent_vertices( vertex( *vi, g ), g ).first; av != boost::adjacent_vertices( vertex( *vi, g ), g ).second; ++av)
        {
            adjacent_vertices[*vi].second.push_back( (int)*av );
        }
    }
}
