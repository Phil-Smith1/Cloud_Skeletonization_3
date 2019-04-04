#pragma once

#include <boost/graph/kruskal_min_spanning_tree.hpp>

#include "Complete_Graph.h"
#include "MST.h"

void Finding_MSTs ( vector<vector<Data_Pt>>const& subcloud, vector<Graph>& mst )
{
    size_t num_intervals = subcloud.size();
    
    mst.resize( num_intervals );
    
    for (int counter = 0; counter < num_intervals; ++counter)
    {
        Graph complete_graph;
        
        Complete_Graph( subcloud[counter], complete_graph );
        
        MST( complete_graph, mst[counter] );
    }
}
