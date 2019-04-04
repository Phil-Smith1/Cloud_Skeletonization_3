#pragma once

#include "Mapper_Parameters.h"
#include "Gauss_Density_Filter.h"
#include "Distance_Filter.h"

void Filter_Function ( vector<Data_Pt>const& cloud, Mapper_Parameters const& parameters, multimap<double, int>& filter_multimap )
{
    if (parameters.filter_function == "Gauss_Density") Gauss_Density_Filter( cloud, parameters.sigma, filter_multimap );
    
    else if (parameters.filter_function == "Distance") Distance_Filter( cloud, filter_multimap );
}
