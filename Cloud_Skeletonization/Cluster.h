#pragma once

#include "Data_Pt.h"

class Cluster
{
    public:
    
    int interval;
    Point2d pt;
    vector<Data_Pt> cloud;
    
    Cluster ( vector<Data_Pt>const& c, Point2d p, int i );
    
    Cluster();
    ~Cluster();
};
