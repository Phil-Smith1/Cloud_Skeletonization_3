#pragma once

#include "Data_Pt.h"

double Gauss_Density ( vector<Data_Pt>const& cloud, Data_Pt const& data_pt, double sigma )
{
    double Gauss_density = 0;
    
    for (auto p : cloud)
    {
        Gauss_density += exp( -pow( norm( data_pt.pt - p.pt ), 2 ) / (double)(2 * pow( sigma, 2 )) );
    }
    
    return Gauss_density;
}

void Gauss_Density_Filter ( vector<Data_Pt>const& cloud, double sigma, multimap<double, int>& filter_multimap )
{
    for (auto p : cloud)
    {
        double Gauss_density = Gauss_Density( cloud, p, sigma );
        
        filter_multimap.insert( pair<double, int>(Gauss_density, p.index) );
    }
}
