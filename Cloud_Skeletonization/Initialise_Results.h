#pragma once

#include "Results.h"

void Initialise_Results ( vector<Results>& mapper_results, vector<double>const& num_intervals_parameter, vector<double>const& DBSCAN_parameter, vector<Results>& alphaReeb_results, vector<double>const& alpha_values, Results& hopes_results, double repetitions )
{
    for (int counter_1 = 0; counter_1 < num_intervals_parameter.size(); ++counter_1)
    {
        for (int counter_2 = 0; counter_2 < DBSCAN_parameter.size(); ++counter_2)
        {
            mapper_results[counter_1 * DBSCAN_parameter.size() + counter_2].parameter_1 = num_intervals_parameter[counter_1];
            mapper_results[counter_1 * DBSCAN_parameter.size() + counter_2].parameter_2 = DBSCAN_parameter[counter_2];
            mapper_results[counter_1 * DBSCAN_parameter.size() + counter_2].time = 0;
            mapper_results[counter_1 * DBSCAN_parameter.size() + counter_2].Betti_success.reserve( repetitions );
            mapper_results[counter_1 * DBSCAN_parameter.size() + counter_2].homeo_success.reserve( repetitions );
            mapper_results[counter_1 * DBSCAN_parameter.size() + counter_2].geom_approx_error.reserve( repetitions );
            mapper_results[counter_1 * DBSCAN_parameter.size() + counter_2].rms.reserve( repetitions );
        }
    }
    
    for (int counter = 0; counter < alpha_values.size(); ++counter)
    {
        alphaReeb_results[counter].parameter_1 = alpha_values[counter];
        alphaReeb_results[counter].time = 0;
        alphaReeb_results[counter].Betti_success.reserve( repetitions );
        alphaReeb_results[counter].homeo_success.reserve( repetitions );
        alphaReeb_results[counter].geom_approx_error.reserve( repetitions );
        alphaReeb_results[counter].rms.reserve( repetitions );
    }
    
    hopes_results.time = 0;
    hopes_results.Betti_success.reserve( repetitions );
    hopes_results.homeo_success.reserve( repetitions );
    hopes_results.geom_approx_error.reserve( repetitions );
    hopes_results.rms.reserve( repetitions );
}
