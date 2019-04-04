#pragma once

#include <vector>

using namespace std;

bool Check_Degrees ( vector<vector<int>>const& vertex_degrees_1, vector<vector<int>>const& vertex_degrees_2 )
{
    if (vertex_degrees_1.size() != vertex_degrees_2.size()) return false;
    
    for (int counter = 0; counter < vertex_degrees_1.size(); ++counter)
    {
        if (vertex_degrees_1[counter].size() != vertex_degrees_2[counter].size()) return false;
    }
    
    return true;
}
