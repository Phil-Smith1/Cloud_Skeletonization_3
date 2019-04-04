#pragma once

#include "Hopes.h"

void Find_Epsilon ( vector<P2>const& cloud, double& epsilon )
{
    double max_birth = 0, min_death = 1e10;
    Graph_H hopes_graph;
    
    Hopes( cloud, hopes_graph, max_birth, min_death );
    
    epsilon = 2 * max_birth + 0.0001;
}
