#pragma once

#include "Graph.h"
#include "Edge.h"

void Extract_Edges ( Graph const& g, vector<pair<P2, P2>>& lines )
{
    lines.reserve( boost::num_edges( g ) );
    
    for (auto ei = boost::edges( g ).first; ei != boost::edges( g ).second; ++ei)
    {
        Point2d pt1 = g[boost::source( *ei, g )].pt;
        Point2d pt2 = g[boost::target( *ei, g )].pt;
        P2 p1( pt1.x, pt1.y );
        P2 p2( pt2.x, pt2.y );
        
        lines.push_back( pair<P2, P2>( p1, p2 ) );
    }
}
