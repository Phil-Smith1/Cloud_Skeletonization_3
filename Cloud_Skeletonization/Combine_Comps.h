#pragma once

#include "Graph.h"

void Combine_Comps ( vector<Graph>const& conn_comp, Graph& g )
{
	for (auto c_c : conn_comp)
	{
		vector<Graph::vertex_descriptor> v;
		vector<pair<Graph::edge_descriptor, bool>> e;

		for (auto vi = boost::vertices( c_c ).first; vi != boost::vertices( c_c ).second; ++vi)
		{
			v.push_back( boost::add_vertex( g ) );
			g[v.back()].pt = c_c[*vi].pt;
		}
        
        for (auto ei = boost::edges( c_c ).first; ei != boost::edges( c_c ).second; ++ei)
        {
            int s = (int)boost::source( *ei, c_c ), t = (int)boost::target( *ei, c_c );
            
            e.push_back( boost::add_edge( v[s], v[t], g ) );
            Point2d source = g[boost::source( e.back().first, g )].pt;
            Point2d target = g[boost::target( e.back().first, g )].pt;
            double length = norm( target - source );
            boost::put( boost::edge_weight_t(), g, e.back().first, length );
        }
	}
}
