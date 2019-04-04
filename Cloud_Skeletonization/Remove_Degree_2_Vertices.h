#pragma once

#include <vector>

using namespace std;

void Remove_Degree_2_Vertices ( vector<pair<int, vector<int>>>& adjacent_vertices )
{
    for (int counter_1 = 0; counter_1 < adjacent_vertices.size(); ++counter_1)
    {
        if (adjacent_vertices[counter_1].second.size() == 2)
        {
            int v1 = adjacent_vertices[counter_1].second[0], v2 = adjacent_vertices[counter_1].second[1];
            
            for (int counter_2 = 0; counter_2 < adjacent_vertices[v1].second.size(); ++counter_2)
            {
                if (adjacent_vertices[v1].second[counter_2] == counter_1)
                {
                    adjacent_vertices[v1].second[counter_2] = v2;
                    break;
                }
            }
            
            for (int counter_2 = 0; counter_2 < adjacent_vertices[v2].second.size(); ++counter_2)
            {
                if (adjacent_vertices[v2].second[counter_2] == counter_1)
                {
                    adjacent_vertices[v2].second[counter_2] = v1;
                    break;
                }
            }
            
            adjacent_vertices.erase( adjacent_vertices.begin() + counter_1 );
            
            for (int counter_2 = 0; counter_2 < adjacent_vertices.size(); ++counter_2)
            {
                if (adjacent_vertices[counter_2].first > counter_1) --adjacent_vertices[counter_2].first;
                
                for (int counter_3 = 0; counter_3 < adjacent_vertices[counter_2].second.size(); ++counter_3)
                {
                    if (adjacent_vertices[counter_2].second[counter_3] > counter_1) --adjacent_vertices[counter_2].second[counter_3];
                }
            }
            
            --counter_1;
        }
    }
}
