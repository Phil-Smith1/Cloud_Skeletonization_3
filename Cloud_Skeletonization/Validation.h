#pragma once

#include "Results.h"
#include "Check_Betti.h"
#include "Is_Homeomorphic.h"
#include "Geometric_Approximation_Error.h"

void Validation ( int expected_Betti_num, Graph const& original_pattern, vector<P2>const& cloud_p, Graph const& g, Results& results )
{
    bool correct_Betti = Check_Betti( expected_Betti_num, g );
    
    results.Betti_success.push_back( correct_Betti );
    
    if (correct_Betti)
    {
        results.homeo_success.push_back( Is_Homeomorphic( original_pattern, g ) );
        
        pair<double, double> geometric_errors = Geometric_Approximation_Error( g, cloud_p );
        
        results.geom_approx_error.push_back( geometric_errors.first );
        results.rms.push_back( geometric_errors.second );
    }
}

void Validation_7Hex ( int expected_Betti_num, Graph const& original_pattern, vector<P2>const& cloud_p, Graph const& g, Results& results )
{
    bool correct_Betti = Check_Betti( expected_Betti_num, g );
    
    results.Betti_success.push_back( correct_Betti );
    
    if (correct_Betti)
    {
        results.homeo_success.push_back( Is_Homeomorphic_7Hex( original_pattern, g ) );
        
        pair<double, double> geometric_errors = Geometric_Approximation_Error( g, cloud_p );
        
        results.geom_approx_error.push_back( geometric_errors.first );
        results.rms.push_back( geometric_errors.second );
    }
}
