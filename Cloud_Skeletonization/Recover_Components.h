#pragma once

#include "Data_Pt.h"
#include "Binary_Search_Tree.h"

void Recover_Components ( Graph const& g, vector<Data_Pt>const& cloud, Graph& component )
{
    vector<Graph::vertex_descriptor> v;
    vector<pair<Graph::edge_descriptor, bool>> e;
    
    size_t cloud_size = cloud.size();
    
    for (int counter = 0; counter < cloud_size; ++counter)
    {
        v.push_back( boost::add_vertex( component ) );
        component[v[counter]].pt = cloud[counter].pt;
        component[v[counter]].index = cloud[counter].index;
    }
    
    Binary_Search_Tree bst;
    
    for (int counter = 0; counter < cloud_size; ++counter)
    {
        bst.insert( cloud[counter].index );
    }
    
    for (auto ei = boost::edges( g ).first; ei != boost::edges( g ).second; ++ei)
    {
        int index_1 = g[boost::source( *ei, g )].index;
        int index_2 = g[boost::target( *ei, g )].index;
        
        if (bst.search( index_1 ) != NULL && bst.search( index_2 ) != NULL)
        {
            int iter_1 = 0, iter_2 = 0;
            
            for (; iter_1 < cloud_size; ++iter_1)
            {
                if (cloud[iter_1].index == index_1) break;
            }
            
            for (; iter_2 < cloud_size; ++iter_2)
            {
                if (cloud[iter_2].index == index_2) break;
            }
            
            e.push_back( boost::add_edge( iter_1, iter_2, component ) );
            Point2d source = component[boost::source( e.back().first, component )].pt;
            Point2d target = component[boost::target( e.back().first, component )].pt;
            double length = norm( target - source );
            boost::put( boost::edge_weight_t(), component, e.back().first, length );
        }
    }
}
