#pragma once

#include <fstream>
#include <iomanip>

#include "Run_Input.h"

void Write_Input ( string const& input_file, Run_Input const& run_input )
{
    ofstream ofs( input_file );
    
    ofs << "Pattern  P_S_1  P_S_2  Reg  G_D_C_S  C_S_Param  Noise_Type  Noise_Parameter  Mapper  Mapper_Simp_Type  AlphaReeb  AlphaReeb_Simp_Type  Hopes  Hopes_Simp_Type  Repetitions" << endl;
    
    for (auto it_1 = run_input.noise_parameter_range.begin(); it_1 != run_input.noise_parameter_range.end(); ++it_1)
    {
        for (auto it_2 = run_input.wheel_range.begin(); it_2 != run_input.wheel_range.end(); ++it_2)
        {
            ofs << left << setw( 11 ) << "wheel";
            ofs << left << setw( 7 ) << *it_2;
            ofs << left << setw( 7 ) << 0;
            ofs << left << setw( 5 ) << run_input.regular;
            ofs << left << setw( 9 ) << run_input.graph_dependent_cloud_size;
            ofs << left << setw( 11 ) << run_input.cloud_size_parameter;
            ofs << left << setw( 12 ) << run_input.noise_type;
            ofs << left << setw( 17 ) << *it_1;
            ofs << left << setw( 8 ) << run_input.mapper;
            ofs << left << setw( 18 ) << run_input.mapper_simp_type;
            ofs << left << setw( 11 ) << run_input.alphaReeb;
            ofs << left << setw( 21 ) << run_input.alphaReeb_simp_type;
            ofs << left << setw( 7 ) << run_input.hopes;
            ofs << left << setw( 17 ) << run_input.hopes_simp_type;
            ofs << left << setw( 13 ) << run_input.repetitions << endl;
        }
        
        for (auto it_2 = run_input.grid_cols_range.begin(); it_2 != run_input.grid_cols_range.end(); ++it_2)
        {
            for (auto it_3 = run_input.grid_rows_range.begin(); it_3 != run_input.grid_rows_range.end(); ++it_3)
            {
                if (*it_3 < *it_2) continue; // Ensures number of rows is >= number of columns.
                
                ofs << left << setw( 11 ) << "grid";
                ofs << left << setw( 7 ) << *it_2;
                ofs << left << setw( 7 ) << *it_3;
                ofs << left << setw( 5 ) << run_input.regular;
                ofs << left << setw( 9 ) << run_input.graph_dependent_cloud_size;
                ofs << left << setw( 11 ) << run_input.cloud_size_parameter;
                ofs << left << setw( 12 ) << run_input.noise_type;
                ofs << left << setw( 17 ) << *it_1;
                ofs << left << setw( 8 ) << run_input.mapper;
                ofs << left << setw( 18 ) << run_input.mapper_simp_type;
                ofs << left << setw( 11 ) << run_input.alphaReeb;
                ofs << left << setw( 21 ) << run_input.alphaReeb_simp_type;
                ofs << left << setw( 7 ) << run_input.hopes;
                ofs << left << setw( 17 ) << run_input.hopes_simp_type;
                ofs << left << setw( 13 ) << run_input.repetitions << endl;
            }
        }
        
        for (auto it_2 = run_input.triangles_range.begin(); it_2 != run_input.triangles_range.end(); ++it_2)
        {
            ofs << left << setw( 11 ) << "triangles";
            ofs << left << setw( 7 ) << *it_2;
            ofs << left << setw( 7 ) << 0;
            ofs << left << setw( 5 ) << run_input.regular;
            ofs << left << setw( 9 ) << run_input.graph_dependent_cloud_size;
            ofs << left << setw( 11 ) << run_input.cloud_size_parameter;
            ofs << left << setw( 12 ) << run_input.noise_type;
            ofs << left << setw( 17 ) << *it_1;
            ofs << left << setw( 8 ) << run_input.mapper;
            ofs << left << setw( 18 ) << run_input.mapper_simp_type;
            ofs << left << setw( 11 ) << run_input.alphaReeb;
            ofs << left << setw( 21 ) << run_input.alphaReeb_simp_type;
            ofs << left << setw( 7 ) << run_input.hopes;
            ofs << left << setw( 17 ) << run_input.hopes_simp_type;
            ofs << left << setw( 13 ) << run_input.repetitions << endl;
        }
        
        for (auto it_2 = run_input.hexagonal_range.begin(); it_2 != run_input.hexagonal_range.end(); ++it_2)
        {
            ofs << left << setw( 11 ) << "hexagonal";
            ofs << left << setw( 7 ) << *it_2;
            ofs << left << setw( 7 ) << 0;
            ofs << left << setw( 5 ) << run_input.regular;
            ofs << left << setw( 9 ) << run_input.graph_dependent_cloud_size;
            ofs << left << setw( 11 ) << run_input.cloud_size_parameter;
            ofs << left << setw( 12 ) << run_input.noise_type;
            ofs << left << setw( 17 ) << *it_1;
            ofs << left << setw( 8 ) << run_input.mapper;
            ofs << left << setw( 18 ) << run_input.mapper_simp_type;
            ofs << left << setw( 11 ) << run_input.alphaReeb;
            ofs << left << setw( 21 ) << run_input.alphaReeb_simp_type;
            ofs << left << setw( 7 ) << run_input.hopes;
            ofs << left << setw( 17 ) << run_input.hopes_simp_type;
            ofs << left << setw( 13 ) << run_input.repetitions << endl;
        }
        
        for (auto it_2 = run_input.squares_range.begin(); it_2 != run_input.squares_range.end(); ++it_2)
        {
            ofs << left << setw( 11 ) << "squares";
            ofs << left << setw( 7 ) << *it_2;
            ofs << left << setw( 7 ) << 0;
            ofs << left << setw( 5 ) << run_input.regular;
            ofs << left << setw( 9 ) << run_input.graph_dependent_cloud_size;
            ofs << left << setw( 11 ) << run_input.cloud_size_parameter;
            ofs << left << setw( 12 ) << run_input.noise_type;
            ofs << left << setw( 17 ) << *it_1;
            ofs << left << setw( 8 ) << run_input.mapper;
            ofs << left << setw( 18 ) << run_input.mapper_simp_type;
            ofs << left << setw( 11 ) << run_input.alphaReeb;
            ofs << left << setw( 21 ) << run_input.alphaReeb_simp_type;
            ofs << left << setw( 7 ) << run_input.hopes;
            ofs << left << setw( 17 ) << run_input.hopes_simp_type;
            ofs << left << setw( 13 ) << run_input.repetitions << endl;
        }
    }
    
    ofs.close();
}
