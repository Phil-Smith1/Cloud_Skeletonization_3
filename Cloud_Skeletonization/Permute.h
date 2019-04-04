#pragma once

#include <vector>

#include "Factorial.h"

using namespace std;

void Permute ( vector<int>& elements, int n )
{
    int num_elements = (int)elements.size();
    
    if (num_elements > 1)
    {
        int f = Factorial( num_elements - 1 ), position = 0;
        
        while (n - (position + 1) * f >= 0) ++position;
        
        int copy = elements[0];
        elements[0] = elements[position];
        elements[position] = copy;
        
        vector<int> remaining_elements;
        
        for (int counter = 0; counter < num_elements; ++counter)
        {
            if (counter != position) remaining_elements.push_back( elements[counter] );
        }
        
        Permute( remaining_elements, n - position * f );
        
        for (int counter = 0; counter < num_elements; ++counter)
        {
            if (counter < position) elements[counter] = remaining_elements[counter];
            
            else if (counter == position) continue;
            
            else if (counter > position) elements[counter] = remaining_elements[counter - 1];
        }
    }
}

void Permute ( vector<int>& elements, int m, int n )
{
    elements.resize( m );
    
    for (int counter = 0; counter < m; ++counter)
    {
        elements[counter] = counter;
    }
    
    Permute( elements, n );
}
