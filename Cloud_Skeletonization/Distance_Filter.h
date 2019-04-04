#pragma once

#include "Data_Pt.h"

void Distance_Filter ( vector<Data_Pt>const& cloud, multimap<double, int>& filter_multimap )
{
    size_t cloud_size = cloud.size(), index_1 = 0, index_2 = 0;
    double max_dist = 0;
    
    for (int counter = 1; counter < cloud_size; ++counter)
    {
        double dist = norm( cloud[counter].pt - cloud[0].pt );
        
        if (dist > max_dist)
        {
            max_dist = dist;
            index_1 = counter;
        }
    }
    
    max_dist = 0;
    
    for (int counter = 0; counter < cloud_size; ++counter)
    {
        double dist = norm( cloud[counter].pt - cloud[index_1].pt );
        
        if (dist > max_dist)
        {
            max_dist = dist;
            index_2 = counter;
        }
    }
    
    for (int counter = 0; counter < cloud_size; ++counter)
    {
        double dist = norm( cloud[counter].pt - cloud[index_2].pt );
        
        filter_multimap.insert( pair<double, int>( dist, counter ) );
    }
}
