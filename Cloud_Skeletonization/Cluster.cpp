#include "Cluster.h"

Cluster::Cluster ( vector<Data_Pt>const& c, Point2d p, int i )
{
    cloud = c;
    pt = p;
    interval = i;
}

Cluster::Cluster(){}
Cluster::~Cluster(){}
