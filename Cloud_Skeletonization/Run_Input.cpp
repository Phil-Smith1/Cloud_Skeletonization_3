#include "Run_Input.h"

Run_Input::Run_Input ( vector<int>const& w_r, vector<int>const& g_c_r, vector<int>const& g_r_r, bool reg, vector<int>const& t_r, vector<int>const& h_r, vector<int>const& s_r, bool g_d_c_s, int c_s_p, string const& n_t, vector<double> n_p_r, bool m, int m_s_t, bool aR, int a_s_t, bool h, int h_s_t, int r )
{
    wheel_range = w_r;
    grid_cols_range = g_c_r;
    grid_rows_range = g_r_r;
    regular = reg;
    triangles_range = t_r;
    hexagonal_range = h_r;
    squares_range = s_r;
    graph_dependent_cloud_size = g_d_c_s;
    cloud_size_parameter = c_s_p;
    noise_type = n_t;
    noise_parameter_range = n_p_r;
    mapper = m;
    mapper_simp_type = m_s_t;
    alphaReeb = aR;
    alphaReeb_simp_type = a_s_t;
    hopes = h;
    hopes_simp_type = h_s_t;
    repetitions = r;
}

Run_Input::Run_Input(){}
Run_Input::~Run_Input(){}
