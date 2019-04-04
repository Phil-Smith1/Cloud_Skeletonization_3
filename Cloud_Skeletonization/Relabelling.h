#pragma once

#include <vector>

using namespace std;

void Relabelling ( vector<pair<int, vector<int>>>& data, vector<int>const& relabelling )
{
    size_t data_size = data.size();
    
    for (int counter_1 = 0; counter_1 < data_size; ++counter_1)
    {
        data[counter_1].first = relabelling[data[counter_1].first];
        
        size_t vector_size = data[counter_1].second.size();
        
        for (int counter_2 = 0; counter_2 < vector_size; ++counter_2)
        {
            data[counter_1].second[counter_2] = relabelling[data[counter_1].second[counter_2]];
        }
    }
}
