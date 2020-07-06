#pragma once

#include "Generate_Adjacent_Vertices.h"
#include "Remove_Degree_2_Vertices.h"
#include "Check_Degrees.h"
#include "Permute.h"
#include "Relabelling.h"
#include "Is_Bijection.h"
#include "Reverse_Relabelling.h"

bool Is_Homeomorphic ( Graph const& g_1, Graph const& g_2 )
{
    vector<pair<int, vector<int>>> adjacent_vertices_1( boost::num_vertices( g_1 ) );
    vector<pair<int, vector<int>>> adjacent_vertices_2( boost::num_vertices( g_2 ) );
    
    Generate_Adjacent_Vertices( g_1, adjacent_vertices_1 );
    
    Generate_Adjacent_Vertices( g_2, adjacent_vertices_2 );
    
    Remove_Degree_2_Vertices( adjacent_vertices_1 );
    
    Remove_Degree_2_Vertices( adjacent_vertices_2 );
    
    vector<vector<int>> vertex_degrees_1;
    vector<vector<int>> vertex_degrees_2;
    
    for (auto v : adjacent_vertices_1)
    {
        while ((int)v.second.size() > (int)vertex_degrees_1.size() - 1) vertex_degrees_1.push_back( vector<int>() );
        
        vertex_degrees_1[(int)v.second.size()].push_back( v.first );
    }
    
    for (auto v : adjacent_vertices_2)
    {
        while ((int)v.second.size() > (int)vertex_degrees_2.size() - 1) vertex_degrees_2.push_back( vector<int>() );
        
        vertex_degrees_2[(int)v.second.size()].push_back( v.first );
    }
    
    if (!Check_Degrees( vertex_degrees_1, vertex_degrees_2 )) return false;
    
    size_t max_degree = vertex_degrees_1.size();
    int num_iters = 1;
    vector<int> factorials( max_degree );
    
    for (int counter = 0; counter < max_degree; ++counter)
    {
        factorials[counter] = Factorial( (int)vertex_degrees_2[counter].size() );
        num_iters *= factorials[counter];
    }
    
    for (int counter_1 = 0; counter_1 < num_iters; ++counter_1)
    {
        int iter = counter_1;
        vector<vector<int>> permutations( max_degree );
        
        for (int counter_2 = 0; counter_2 < max_degree; ++counter_2)
        {
            int n = iter % factorials[counter_2];
            vector<int> elements;
            
            Permute( elements, (int)vertex_degrees_2[counter_2].size(), n );
            
            permutations[counter_2] = elements;
            
            iter = (iter - n) / factorials[counter_2];
        }
        
        vector<int> relabelling( adjacent_vertices_2.size(), 0 );
        
        for (int counter_2 = 0; counter_2 < max_degree; ++counter_2)
        {
            if (vertex_degrees_2[counter_2].size() == 0) continue;
            
            for (int counter_3 = 0; counter_3 < permutations[counter_2].size(); ++counter_3)
            {
                relabelling[vertex_degrees_2[counter_2][counter_3]] = vertex_degrees_1[counter_2][permutations[counter_2][counter_3]];
            }
        }
        
        Relabelling( adjacent_vertices_2, relabelling );
        
        if (Is_Bijection( adjacent_vertices_1, adjacent_vertices_2 )) return true;
        
        Reverse_Relabelling( relabelling );
        
        Relabelling( adjacent_vertices_2, relabelling );
    }
    
    return false;
}

bool Is_Homeomorphic_7Hex ( Graph const& g_1, Graph const& g_2 )
{
    vector<pair<int, vector<int>>> adjacent_vertices_1( boost::num_vertices( g_1 ) );
    vector<pair<int, vector<int>>> adjacent_vertices_2( boost::num_vertices( g_2 ) );
    
    Generate_Adjacent_Vertices( g_1, adjacent_vertices_1 );
    
    Generate_Adjacent_Vertices( g_2, adjacent_vertices_2 );
    
    Remove_Degree_2_Vertices( adjacent_vertices_1 );
    
    Remove_Degree_2_Vertices( adjacent_vertices_2 );
    
    vector<vector<int>> vertex_degrees_1;
    vector<vector<int>> vertex_degrees_2;
    
    for (auto v : adjacent_vertices_1)
    {
        while ((int)v.second.size() > (int)vertex_degrees_1.size() - 1) vertex_degrees_1.push_back( vector<int>() );
        
        vertex_degrees_1[(int)v.second.size()].push_back( v.first );
    }
    
    for (auto v : adjacent_vertices_2)
    {
        while ((int)v.second.size() > (int)vertex_degrees_2.size() - 1) vertex_degrees_2.push_back( vector<int>() );
        
        vertex_degrees_2[(int)v.second.size()].push_back( v.first );
    }
    
    if (!Check_Degrees( vertex_degrees_1, vertex_degrees_2 )) return false;
    
    int i = vertex_degrees_1[3][1];
    vertex_degrees_1[3][1] = adjacent_vertices_1[0].second[0];
    vertex_degrees_1[3][adjacent_vertices_1[0].second[0]] = i;
    i = vertex_degrees_1[3][2];
    vertex_degrees_1[3][2] = adjacent_vertices_1[0].second[1];
    vertex_degrees_1[3][adjacent_vertices_1[0].second[1]] = i;
    i = vertex_degrees_1[3][3];
    vertex_degrees_1[3][3] = adjacent_vertices_1[0].second[2];
    vertex_degrees_1[3][adjacent_vertices_1[0].second[2]] = i;
    
    i = vertex_degrees_2[3][1];
    vertex_degrees_2[3][1] = adjacent_vertices_2[0].second[0];
    vertex_degrees_2[3][adjacent_vertices_2[0].second[0]] = i;
    i = vertex_degrees_2[3][2];
    vertex_degrees_2[3][2] = adjacent_vertices_2[0].second[1];
    vertex_degrees_2[3][adjacent_vertices_2[0].second[1]] = i;
    i = vertex_degrees_2[3][3];
    vertex_degrees_2[3][3] = adjacent_vertices_2[0].second[2];
    vertex_degrees_2[3][adjacent_vertices_2[0].second[2]] = i;
    
    size_t max_degree = vertex_degrees_1.size();
    int num_iters = 1;
    vector<int> factorials( max_degree );
    
    factorials[0] = 1;
    factorials[1] = 1;
    factorials[2] = 1;
    factorials[3] = 40320;
    
    for (int counter = 0; counter < max_degree; ++counter)
    {
        num_iters *= factorials[counter];
    }
    
    for (int counter_1 = 0; counter_1 < num_iters; ++counter_1)
    {
        int iter = counter_1;
        vector<vector<int>> permutations( max_degree );
        
        for (int counter_2 = 0; counter_2 < max_degree; ++counter_2)
        {
            int n = iter % factorials[counter_2];
            vector<int> elements;
            
            if (counter_2 == 3) Permute( elements, 8, n );
            else Permute( elements, (int)vertex_degrees_2[counter_2].size(), n );
            
            permutations[counter_2] = elements;
            
            iter = (iter - n) / factorials[counter_2];
        }
        
        vector<int> relabelling( adjacent_vertices_2.size(), 0 );
        
        for (int counter_2 = 0; counter_2 < max_degree; ++counter_2)
        {
            if (vertex_degrees_2[counter_2].size() == 0) continue;
            
            if (counter_2 == 3)
            {
                relabelling[vertex_degrees_2[counter_2][0]] = vertex_degrees_1[counter_2][0];
                relabelling[vertex_degrees_2[counter_2][1]] = vertex_degrees_1[counter_2][1];
                relabelling[vertex_degrees_2[counter_2][2]] = vertex_degrees_1[counter_2][2];
                relabelling[vertex_degrees_2[counter_2][3]] = vertex_degrees_1[counter_2][3];
                
                for (int counter_3 = 0; counter_3 < permutations[counter_2].size(); ++counter_3)
                {
                    relabelling[vertex_degrees_2[counter_2][counter_3 + 4]] = vertex_degrees_1[counter_2][permutations[counter_2][counter_3] + 4];
                }
            }
            
            else
            {
                for (int counter_3 = 0; counter_3 < permutations[counter_2].size(); ++counter_3)
                {
                    relabelling[vertex_degrees_2[counter_2][counter_3]] = vertex_degrees_1[counter_2][permutations[counter_2][counter_3]];
                }
            }
        }
        
        Relabelling( adjacent_vertices_2, relabelling );
        
        if (Is_Bijection( adjacent_vertices_1, adjacent_vertices_2 )) return true;
        
        Reverse_Relabelling( relabelling );
        
        Relabelling( adjacent_vertices_2, relabelling );
        
        for (int counter_2 = 0; counter_2 < max_degree; ++counter_2)
        {
            if (vertex_degrees_2[counter_2].size() == 0) continue;
            
            if (counter_2 == 3)
            {
                relabelling[vertex_degrees_2[counter_2][0]] = vertex_degrees_1[counter_2][0];
                relabelling[vertex_degrees_2[counter_2][1]] = vertex_degrees_1[counter_2][1];
                relabelling[vertex_degrees_2[counter_2][2]] = vertex_degrees_1[counter_2][3];
                relabelling[vertex_degrees_2[counter_2][3]] = vertex_degrees_1[counter_2][2];
                
                for (int counter_3 = 0; counter_3 < permutations[counter_2].size(); ++counter_3)
                {
                    relabelling[vertex_degrees_2[counter_2][counter_3 + 4]] = vertex_degrees_1[counter_2][permutations[counter_2][counter_3] + 4];
                }
            }
            
            else
            {
                for (int counter_3 = 0; counter_3 < permutations[counter_2].size(); ++counter_3)
                {
                    relabelling[vertex_degrees_2[counter_2][counter_3]] = vertex_degrees_1[counter_2][permutations[counter_2][counter_3]];
                }
            }
        }
        
        Relabelling( adjacent_vertices_2, relabelling );
        
        if (Is_Bijection( adjacent_vertices_1, adjacent_vertices_2 )) return true;
        
        Reverse_Relabelling( relabelling );
        
        Relabelling( adjacent_vertices_2, relabelling );
        
        for (int counter_2 = 0; counter_2 < max_degree; ++counter_2)
        {
            if (vertex_degrees_2[counter_2].size() == 0) continue;
            
            if (counter_2 == 3)
            {
                relabelling[vertex_degrees_2[counter_2][0]] = vertex_degrees_1[counter_2][0];
                relabelling[vertex_degrees_2[counter_2][1]] = vertex_degrees_1[counter_2][3];
                relabelling[vertex_degrees_2[counter_2][2]] = vertex_degrees_1[counter_2][1];
                relabelling[vertex_degrees_2[counter_2][3]] = vertex_degrees_1[counter_2][2];
                
                for (int counter_3 = 0; counter_3 < permutations[counter_2].size(); ++counter_3)
                {
                    relabelling[vertex_degrees_2[counter_2][counter_3 + 4]] = vertex_degrees_1[counter_2][permutations[counter_2][counter_3] + 4];
                }
            }
            
            else
            {
                for (int counter_3 = 0; counter_3 < permutations[counter_2].size(); ++counter_3)
                {
                    relabelling[vertex_degrees_2[counter_2][counter_3]] = vertex_degrees_1[counter_2][permutations[counter_2][counter_3]];
                }
            }
        }
        
        Relabelling( adjacent_vertices_2, relabelling );
        
        if (Is_Bijection( adjacent_vertices_1, adjacent_vertices_2 )) return true;
        
        Reverse_Relabelling( relabelling );
        
        Relabelling( adjacent_vertices_2, relabelling );
    }
    
    return false;
}
