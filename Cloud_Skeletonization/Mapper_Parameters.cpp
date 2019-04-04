#include "Mapper_Parameters.h"

Mapper_Parameters::Mapper_Parameters ( int n_i, double o_r, string const& f_f, double s, double db, double m )
{
    num_intervals = n_i;
    overlap_ratio = o_r;
    filter_function = f_f;
    sigma = s;
    DBSCAN = db;
    mcsf = m;
}

Mapper_Parameters::Mapper_Parameters(){}
Mapper_Parameters::~Mapper_Parameters(){}

