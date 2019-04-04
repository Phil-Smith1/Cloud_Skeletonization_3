#pragma once

#include "Graph.h"

size_t Betti_Num ( Graph const& g )
{
	size_t Betti_num = 1 - boost::num_vertices( g ) + boost::num_edges( g );
    
	return Betti_num;
}
