#pragma once

#include <vector>

using namespace std;

class Region
{
    public:
    
    int index; // Index of this region in Map.
    int edge; // Index of the critical edge in DelEdges that created this region.
    double birth, death, span;
    vector<int> core; // Indices of triangles that were last alive before this region died.
    int heir; // Index of the root triangle in the older region that absorbed this region.
    int supr; // Index of the region (in Map) defined by the triangle heir, computed at the end.
    
    Region ( int i, double b, double d, vector<int>const& c, int h, int s, int e );
    
    Region();
    ~Region();
};
