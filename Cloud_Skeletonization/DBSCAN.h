#pragma once

#include "Geometric_Centre_Of_Cloud.h"
#include "Cluster.h"

bool In_Neighbourhood ( Data_Pt a, Data_Pt b, double epsilon )
{
    if (norm( a.pt - b.pt ) < epsilon) return true;
    
    else return false;
}

void Neighbours ( vector<Data_Pt>const& cloud, int pt, double epsilon, vector<int>& neighbours )
{
    for (int counter_1 = 0; counter_1 < cloud.size(); ++counter_1)
    {
        if (counter_1 == pt) continue;
        
        if (In_Neighbourhood( cloud[pt], cloud[counter_1], epsilon )) neighbours.push_back( counter_1 );
    }
}

void DBSCAN ( vector<Data_Pt>const& cloud, double epsilon, int min_pts, int interval, vector<Cluster>& cluster )
{
    int cluster_counter = 0;
    vector<int> label( cloud.size(), 0 );
    
    for (int counter_1 = 0; counter_1 < cloud.size(); ++counter_1)
    {
        if (label[counter_1] != 0) continue;
        
        vector<int> neighbours;
        neighbours.push_back( counter_1 );
        
        Neighbours( cloud, counter_1, epsilon, neighbours );
        
        if (neighbours.size() < min_pts)
        {
            label[counter_1] = -1;
            continue;
        }
        
        ++cluster_counter;
        
        label[counter_1] = cluster_counter;
        
        for (int counter_2 = 1; counter_2 < neighbours.size(); ++counter_2)
        {
            if (label[neighbours[counter_2]] == -1) label[neighbours[counter_2]] = cluster_counter;
            
            if (label[neighbours[counter_2]] != 0) continue;
            
            label[neighbours[counter_2]] = cluster_counter;
            
            vector<int> new_neighbours;
            new_neighbours.push_back( neighbours[counter_2] );
            
            Neighbours( cloud, neighbours[counter_2], epsilon, new_neighbours );
            
            if (new_neighbours.size() >= min_pts)
            {
                for (int counter_3 = 1; counter_3 < new_neighbours.size(); ++counter_3)
                {
                    bool found = false;
                    int current_size = (int)neighbours.size();
                    
                    for (int counter_4 = 0; counter_4 < current_size; ++counter_4)
                    {
                        if (neighbours[counter_4] == new_neighbours[counter_3])
                        {
                            found = true;
                            break;
                        }
                    }
                    
                    if (!found) neighbours.push_back( new_neighbours[counter_3] );
                }
            }
        }
    }
    
    vector<vector<Data_Pt>> list( cluster_counter );
    
    for (int counter = 0; counter < cloud.size(); ++counter)
    {
        if (label[counter] <= 0) continue;
        
        list[label[counter] - 1].push_back( cloud[counter] );
    }
    
    for (int counter = 0; counter < cluster_counter; ++counter)
    {
        cluster.push_back( Cluster( list[counter], Geometric_Centre_Of_Cloud( list[counter] ), interval ) );
    }
}
