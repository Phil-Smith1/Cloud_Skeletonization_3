#pragma once

#include "Data_Pt.h"
#include "Edge.h"

void Convert_Cloud_1 ( vector<Data_Pt>const& initial_cloud, vector<P2>& converted_cloud )
{
    for (auto p : initial_cloud)
    {
        converted_cloud.push_back( P2( p.pt.x, p.pt.y ) );
    }
}

void Convert_Cloud_2 ( vector<P2>const& initial_cloud, vector<Data_Pt>& converted_cloud )
{
    for (auto p : initial_cloud)
    {
        converted_cloud.push_back( Data_Pt( Point2d( p.x(), p.y() ) ) );
    }
    
    for (int counter = 0; counter < converted_cloud.size(); ++counter)
    {
        converted_cloud[counter].index = counter;
    }
}
