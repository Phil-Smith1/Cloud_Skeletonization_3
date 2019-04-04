#include "Input.h"

Input::Input ( string const& p_t, int p_s_1, int p_s_2, bool reg, bool g_d_c_s, int c_s_p, string const& n_t, double n_p, bool m, int m_s_t, bool aR, int a_s_t, bool h, int h_s_t, int r )
{
    pattern_type = p_t;
    pattern_size_1 = p_s_1;
    pattern_size_2 = p_s_2;
    regular = reg;
    graph_dependent_cloud_size = g_d_c_s;
    cloud_size_parameter = c_s_p;
    noise_type = n_t;
    noise_parameter = n_p;
    mapper = m;
    mapper_simp_type = m_s_t;
    alphaReeb = aR;
    alphaReeb_simp_type = a_s_t;
    hopes = h;
    hopes_simp_type = h_s_t;
    repetitions = r;
}

Input::Input(){}
Input::~Input(){}
