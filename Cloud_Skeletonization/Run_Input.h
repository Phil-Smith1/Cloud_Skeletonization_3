#pragma once

#include <string>
#include <vector>

using namespace std;

class Run_Input
{
    public:
    
    bool graph_dependent_cloud_size, regular, mapper, alphaReeb, hopes;
    int cloud_size_parameter, mapper_simp_type, alphaReeb_simp_type, hopes_simp_type, repetitions;
    string noise_type;
    vector<int> wheel_range, grid_cols_range, grid_rows_range, triangles_range, hexagonal_range, squares_range;
    vector<double> noise_parameter_range;
    
    Run_Input ( vector<int>const& w_r, vector<int>const& g_c_r, vector<int>const& g_r_r, bool reg, vector<int>const& t_r, vector<int>const& h_r, vector<int>const& s_r, bool g_d_c_s, int c_s_p, string const& n_t, vector<double> n_p_r, bool m, int m_s_t, bool aR, int a_s_t, bool h, int h_s_t, int r );
    
    Run_Input();
    ~Run_Input();
};
