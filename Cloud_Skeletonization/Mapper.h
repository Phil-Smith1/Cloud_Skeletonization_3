#pragma once

#include "Filter_Function.h"
#include "Generate_Subclouds.h"
#include "DBSCAN.h"
#include "Clustering.h"
#include "Output_Graph.h"

void Mapper ( vector<Data_Pt>const& cloud, Mapper_Parameters const& parameters, Graph& mapper_graph )
{
    multimap<double, int> filter_multimap; // Key = filter value, value = index.
    
    Filter_Function( cloud, parameters, filter_multimap ); // Assigning the filter value to each point.
    
    vector<vector<Data_Pt>> subcloud;
    
    Generate_Subclouds( cloud, filter_multimap, parameters.num_intervals, parameters.overlap_ratio, subcloud ); // Assigning points to subclouds.
    
    vector<Cluster> cluster;
    
    for (int counter = 0; counter < parameters.num_intervals; ++counter)
    {
        DBSCAN( subcloud[counter], parameters.DBSCAN, 5, counter, cluster ); // Clustering subclouds using the DBSCAN algorithm.
    }
    
    double min_comp_size = cloud.size() * parameters.mcsf;
    
    Output_Graph( cluster, min_comp_size, mapper_graph ); // Producing the output graph.
}
