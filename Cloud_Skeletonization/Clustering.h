#pragma once

#include "Reduce_MSTs.h"
#include "Group_Subgraphs.h"

void Clustering ( vector<vector<Data_Pt>>const& subcloud, vector<Graph>& mst, vector<Cluster>& cluster )
{
    size_t num_intervals = subcloud.size();
    
    vector<Graph> g;
        
    Reduce_MSTs( mst, g );
    
    for (int counter = 0; counter < num_intervals; ++counter)
    {
        Grouping( g[counter], subcloud[counter], counter, cluster );
    }
}
