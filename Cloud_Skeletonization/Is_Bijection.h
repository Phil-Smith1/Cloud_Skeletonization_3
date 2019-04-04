#pragma once

#include <vector>

using namespace std;

bool Is_Bijection ( vector<pair<int, vector<int>>>const& adjacent_vertices_1, vector<pair<int, vector<int>>>const& adjacent_vertices_2 )
{
    for (int counter_1 = 0; counter_1 < adjacent_vertices_1.size(); ++counter_1)
    {
        int vertex = adjacent_vertices_1[counter_1].first, counter_2 = 0;
        
        for (; counter_2 < adjacent_vertices_2.size(); ++counter_2)
        {
            if (adjacent_vertices_2[counter_2].first == vertex) break;
        }
        
        for (int counter_3 = 0; counter_3 < adjacent_vertices_1[counter_1].second.size(); ++counter_3)
        {
            bool found = false;
            
            for (int counter_4 = 0; counter_4 < adjacent_vertices_2[counter_2].second.size(); ++counter_4)
            {
                if (adjacent_vertices_1[counter_1].second[counter_3] == adjacent_vertices_2[counter_2].second[counter_4])
                {
                    found = true;
                    break;
                }
            }
            
            if (!found) return false;
        }
    }
    
    return true;
}
