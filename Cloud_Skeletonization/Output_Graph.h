#pragma once

#include "Data_Pt.h"
#include "Connect_Clusters.h"
#include "Remove_Small_Mapper_Components.h"

void Output_Graph ( vector<Cluster>const& cluster, double min_comp_size, Graph& output_graph )
{
    Connect_Clusters( cluster, output_graph );
    
    Remove_Small_Mapper_Components( output_graph, cluster, min_comp_size );
}
