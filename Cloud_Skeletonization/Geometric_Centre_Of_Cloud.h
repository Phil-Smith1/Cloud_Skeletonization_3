#pragma once

#include "Data_Pt.h"

Point2d Geometric_Centre_Of_Cloud ( vector<Data_Pt>const& cloud )
{
    size_t cloud_size = cloud.size();
    Point2d geometric_centre = Point2d( 0, 0 );
    
    for (auto p : cloud)
    {
        geometric_centre += p.pt;
    }
    
    geometric_centre = geometric_centre / (double)cloud_size;
    
    return geometric_centre;
}
