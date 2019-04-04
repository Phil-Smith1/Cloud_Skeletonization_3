#include "Region.h"

Region::Region ( int i, double b, double d, vector<int>const& c, int h, int s, int e )
{
    index = i;
    birth = b;
    death = d;
    span = d - b;
    core = c;
    heir = h;
    supr = s;
    edge = e;
}

Region::Region(){}
Region::~Region(){}
