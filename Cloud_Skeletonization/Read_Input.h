#pragma once

#include <sstream>

#include "Input.h"

void Read_Input ( string const& line_data, Input& input )
{
    bool g_d_c_s, reg, m, aR, h;
    int p_s_1, p_s_2, c_s_p, r, m_s_t, a_s_t, h_s_t;
    double n_p;
    string p_t, n_t;
    stringstream stream;
    
    stream << line_data;
    
    stream >> p_t >> p_s_1 >> p_s_2 >> reg >> g_d_c_s >> c_s_p >> n_t >> n_p >> m >> m_s_t >> aR >> a_s_t >> h >> h_s_t >> r;
    
    if (p_t != "grid") reg = true;
    
    Input inp( p_t, p_s_1, p_s_2, reg, g_d_c_s, c_s_p, n_t, n_p, m, m_s_t, aR, a_s_t, h, h_s_t, r );
    
    input = inp;
}
