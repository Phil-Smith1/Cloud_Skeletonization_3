#pragma once

#include <string>

using namespace std;

class Input
{
    public:
    
    bool graph_dependent_cloud_size, regular, mapper, alphaReeb, hopes, graph_dependent_num_intervals;
    int pattern_size_1, pattern_size_2, cloud_size_parameter, repetitions, num_intervals = 0, mapper_simp_type, alphaReeb_simp_type, hopes_simp_type;
    double noise_parameter, alpha = 0, num_intervals_param = 0, DBSCAN_parameter = 0;
    string pattern_type, noise_type;
    
    Input ( string const& p_t, int p_s_1, int p_s_2, bool reg, bool g_d_c_s, int c_s_p, string const& n_t, double n_p, bool m, int m_s_t, bool aR, int a_s_t, bool h, int h_s_t, int r );
    
    Input();
    ~Input();
};
