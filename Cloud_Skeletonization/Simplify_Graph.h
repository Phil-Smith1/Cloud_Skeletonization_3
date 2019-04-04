#pragma once

#include "Convert_Graph.h"
#include "Remove_Degree_1_Vertices.h"
#include "Simplify_Graph_2.h"
#include "Simplify_HoPeS.h"

void Simplify_Graph ( Graph& g, int simp_type )
{
    if (simp_type == 1)
    {
        Remove_Degree_1_Vertices( g );
    }
}

void Simplify_Graph ( Graph_H& g_1, int simp_type, double min_death, double mcsf, Graph& g_2 )
{
    if (simp_type == 0)
    {
        Convert_Graph( g_1, g_2 );
    }
    
    if (simp_type == 1)
    {
        Remove_Degree_1_Vertices( g_1 );
        
        Convert_Graph( g_1, g_2 );
    }
    
    if (simp_type == 2)
    {
        Remove_Degree_1_Vertices( g_1 );
        
        Simplify_HoPeS( g_1, min_death );
        
        Convert_Graph( g_1, g_2 );
    }
    
    if (simp_type == 3)
    {
        Remove_Degree_1_Vertices( g_1 );
        
        Simplify_HoPeS( g_1, 2 * min_death );
        
        Convert_Graph( g_1, g_2 );
    }
    
    if (simp_type == 4)
    {
        Convert_Graph( g_1, g_2 );
        
        if (min_death > 0.3) min_death = 0.3; // Capping min_death at 0.3.
        
        AlphaReeb_Parameters parameters( 2 * min_death, mcsf );
        Graph aR;
        
        AlphaReeb_Algorithm( g_2, parameters, aR );
        
        Remove_Degree_1_Vertices( aR );
        
        g_2 = aR;
    }
    
    if (simp_type == 5)
    {
        Remove_Degree_1_Vertices( g_1 );
        
        Convert_Graph( g_1, g_2 );
        
        if (min_death > 0.3) min_death = 0.3; // Capping min_death at 0.3.
        
        AlphaReeb_Parameters parameters( 2 * min_death, mcsf );
        Graph aR;
        
        AlphaReeb_Algorithm( g_2, parameters, aR );
        
        Remove_Degree_1_Vertices( aR );
        
        g_2 = aR;
    }
    
    if (simp_type == 6)
    {
        Convert_Graph( g_1, g_2 );
        
        Simplify_Graph_2( g_2 );
    }
    
    if (simp_type == 7)
    {
        Simplify_HoPeS( g_1, min_death );
        
        Convert_Graph( g_1, g_2 );
    }
}
