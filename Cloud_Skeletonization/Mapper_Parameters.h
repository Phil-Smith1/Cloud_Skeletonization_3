#pragma once

#include <string>

using namespace std;

class Mapper_Parameters
{
    public:
    
    int num_intervals;
    double mcsf, overlap_ratio, sigma, DBSCAN;
    string filter_function;
    
    Mapper_Parameters ( int n_i, double o_r, string const& f_f, double s, double db, double m );
    
    Mapper_Parameters();
    ~Mapper_Parameters();
};
