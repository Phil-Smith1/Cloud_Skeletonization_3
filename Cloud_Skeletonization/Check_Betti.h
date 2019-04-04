#pragma once

#include <boost/graph/connected_components.hpp>

#include "Betti_Num.h"

bool Check_Betti ( size_t expected_Betti_num, Graph const& output_graph )
{
    size_t num_vertices = boost::num_vertices( output_graph );
    vector<int> comp( num_vertices );
    
    int num_comps = boost::connected_components( output_graph, &comp[0] );
    
    if (num_comps > 1) return false; // Returns false if output graph more than one connected component.
    
    if (expected_Betti_num == Betti_Num( output_graph )) return true;
    
    else return false;
}
