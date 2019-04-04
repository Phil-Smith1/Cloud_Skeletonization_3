#pragma once

#include "Graph_H.h"
#include "Single_Edge_Clustering.h"
#include "Find_Diagonal_Gaps.h"
#include "Draw_1D_PD.h"

void Hopes ( vector<P2>const& cloud, Graph_H& hopes_graph, double& max_birth, double& min_death )
{
    vector<vector<P2>> clouds;
    clouds.assign( 1, cloud );
    
    Single_Edge_Clustering( 3, clouds );
    
    size_t cloud_size = clouds.size();
    
    for (int counter = 0; counter < cloud_size; ++counter)
    {
        if (clouds[counter].size() < 9) continue;
        
        Filtration filtration( clouds[counter] );
        
        if (filtration.delaunay.number_of_faces() == 0) continue;
        
        filtration.Persistence1d( );
        
        int num_dots = (int)filtration.persistence.size(), index_above_gap;
        vector<int> graph_edges = filtration.negative_edges;
        vector<IndexValue> diagonal_gaps( num_dots );
        
        if (filtration.persistence.size())
        {
            Find_Diagonal_Gaps( filtration.persistence, index_above_gap, diagonal_gaps );
            
            for (int counter = index_above_gap; counter < filtration.persistence.size(); ++counter)
            {
                graph_edges.push_back( filtration.persistence[counter].edge );
                if (filtration.persistence[counter].birth > max_birth) max_birth = filtration.persistence[counter].birth;
                if (filtration.persistence[counter].death < min_death) min_death = filtration.persistence[counter].death;
            }
            
            /*///////////////// Uncomment to draw 1D PD.
            
            const Point image_sizes( 800, 800 );
            Mat image( image_sizes, CV_8UC3, CV_RGB( 255, 255, 255 ) );
            
            Draw_1D_PD(filtration.persistence, index_above_gap, image );
            
            imwrite( "/Users/philsmith/Documents/Xcode Projects/Cloud_Skeletonization/pd.png", image );
            
            ////////////////*/
        }
        
        hopes_graph.Initialise_Graph( filtration.edges, graph_edges, (int)filtration.delaunay.number_of_vertices() );
    }
}
