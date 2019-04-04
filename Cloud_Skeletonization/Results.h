#pragma once

#include <vector>

using namespace std;

class Results
{
    public:
    
    double parameter_1, parameter_2, time, mean_time, Betti_success_rate, homeo_success_rate, mgae, mrms;
    vector<bool> Betti_success, homeo_success;
    vector<double> geom_approx_error, rms;
    
    Results();
    ~Results();
};
