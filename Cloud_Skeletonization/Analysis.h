#pragma once

#include <fstream>
#include <iomanip>

#include "Input.h"
#include "Results.h"

void Analysis ( string const& result_directory, Input const& input, size_t mean_cloud_size, vector<Results>& mapper_results, vector<Results>& alphaReeb_results, Results& hopes_results )
{
    if (input.mapper)
    {
        int optimal_Betti = 0, optimal_homeo = 0, optimal_mgae = 0, optimal_mrms = 0;
        double best_Betti = 0, best_homeo = 0, best_mgae = 1e10, best_mrms = 1e10;
        
        for (int counter = 0; counter < mapper_results.size(); ++counter)
        {
            int Betti_successes = 0, homeo_successes = 0;
            double gae = 0, rms = 0;
            
            for (auto r : mapper_results[counter].Betti_success) if (r) ++Betti_successes;
            
            for (auto r : mapper_results[counter].homeo_success) if (r) ++homeo_successes;
            
            for (auto r : mapper_results[counter].geom_approx_error) gae += r;
            
            for (auto r : mapper_results[counter].rms) rms += r;
            
            mapper_results[counter].Betti_success_rate = 100 * Betti_successes / (double)mapper_results[counter].Betti_success.size();
            
            if (mapper_results[counter].homeo_success.size() > 0) mapper_results[counter].homeo_success_rate = 100 * homeo_successes / (double)mapper_results[counter].homeo_success.size();
            else mapper_results[counter].homeo_success_rate = 0;
            
            if (mapper_results[counter].geom_approx_error.size() > 0) mapper_results[counter].mgae = gae / (double)mapper_results[counter].geom_approx_error.size();
            else mapper_results[counter].mgae = 1e10;
            
            if (mapper_results[counter].rms.size() > 0) mapper_results[counter].mrms = rms / (double)mapper_results[counter].rms.size();
            else mapper_results[counter].mrms = 1e10;
            
            if (mapper_results[counter].Betti_success_rate >= best_Betti)
            {
                best_Betti = mapper_results[counter].Betti_success_rate;
                optimal_Betti = counter;
            }
            
            if (mapper_results[counter].homeo_success_rate >= best_homeo)
            {
                best_homeo = mapper_results[counter].homeo_success_rate;
                optimal_homeo = counter;
            }
            
            if (mapper_results[counter].mgae <= best_mgae)
            {
                best_mgae = mapper_results[counter].mgae;
                optimal_mgae = counter;
            }
            
            if (mapper_results[counter].mrms <= best_mrms)
            {
                best_mrms = mapper_results[counter].mrms;
                optimal_mrms = counter;
            }
        }
        
        mapper_results[optimal_Betti].mean_time = mapper_results[optimal_Betti].time / (double)input.repetitions;
        
        string result_file = result_directory + "Mapper/List_Of_Results/Mapper_hex.txt";
        
        ofstream ofs( result_file, ios::app );
        
        ofs << left << setw( 11 ) << input.pattern_type;
        ofs << left << setw( 7 ) << input.pattern_size_1;
        ofs << left << setw( 7 ) << input.pattern_size_2;
        ofs << left << setw( 5 ) << input.regular;
        ofs << left << setw( 9 ) << mean_cloud_size;
        ofs << left << setw( 12 ) << input.noise_type;
        ofs << left << setw( 13 ) << input.noise_parameter;
        ofs << left << setw( 12 ) << input.repetitions;
        ofs << left << setw( 11 ) << "Mapper";
        ofs << left << setw( 6 ) << input.mapper_simp_type;
        ofs << left << setw( 13 ) << mapper_results[optimal_Betti].Betti_success_rate;
        ofs << left << setw( 13 ) << mapper_results[optimal_homeo].homeo_success_rate;
        ofs << left << setw( 11 ) << mapper_results[optimal_mgae].mgae;
        ofs << left << setw( 12 ) << mapper_results[optimal_mrms].mrms;
        ofs << left << setw( 5 ) << mapper_results[optimal_Betti].parameter_1;
        ofs << left << setw( 6 ) << mapper_results[optimal_Betti].parameter_2;
        ofs << left << setw( 5 ) << mapper_results[optimal_homeo].parameter_1;
        ofs << left << setw( 6 ) << mapper_results[optimal_homeo].parameter_2;
        ofs << left << setw( 5 ) << mapper_results[optimal_mgae].parameter_1;
        ofs << left << setw( 6 ) << mapper_results[optimal_mgae].parameter_2;
        ofs << left << setw( 5 ) << mapper_results[optimal_mrms].parameter_1;
        ofs << left << setw( 6 ) << mapper_results[optimal_mrms].parameter_2;
        ofs << left << setw( 8 ) << mapper_results[optimal_Betti].mean_time << endl;
        
        ofs.close();
    }
    
    if (input.alphaReeb)
    {
        int optimal_Betti = 0, optimal_homeo = 0, optimal_mgae = 0, optimal_mrms = 0;
        double best_Betti = 0, best_homeo = 0, best_mgae = 1e10, best_mrms = 1e10;
        
        for (int counter = 0; counter < alphaReeb_results.size(); ++counter)
        {
            int Betti_successes = 0, homeo_successes = 0;
            double gae = 0, rms = 0;
            
            for (auto r : alphaReeb_results[counter].Betti_success) if (r) ++Betti_successes;
            
            for (auto r : alphaReeb_results[counter].homeo_success) if (r) ++homeo_successes;
            
            for (auto r : alphaReeb_results[counter].geom_approx_error) gae += r;
            
            for (auto r : alphaReeb_results[counter].rms) rms += r;
            
            alphaReeb_results[counter].Betti_success_rate = 100 * Betti_successes / (double)alphaReeb_results[counter].Betti_success.size();
            
            if (alphaReeb_results[counter].homeo_success.size() > 0) alphaReeb_results[counter].homeo_success_rate = 100 * homeo_successes / (double)alphaReeb_results[counter].homeo_success.size();
            else alphaReeb_results[counter].homeo_success_rate = 0;
            
            if (alphaReeb_results[counter].geom_approx_error.size() > 0) alphaReeb_results[counter].mgae = gae / (double)alphaReeb_results[counter].geom_approx_error.size();
            else alphaReeb_results[counter].mgae = 1e10;
            
            if (alphaReeb_results[counter].rms.size() > 0) alphaReeb_results[counter].mrms = rms / (double)alphaReeb_results[counter].rms.size();
            else alphaReeb_results[counter].mrms = 1e10;
            
            if (alphaReeb_results[counter].Betti_success_rate > best_Betti)
            {
                best_Betti = alphaReeb_results[counter].Betti_success_rate;
                optimal_Betti = counter;
            }
            
            if (alphaReeb_results[counter].homeo_success_rate > best_homeo)
            {
                best_homeo = alphaReeb_results[counter].homeo_success_rate;
                optimal_homeo = counter;
            }
            
            if (alphaReeb_results[counter].mgae < best_mgae)
            {
                best_mgae = alphaReeb_results[counter].mgae;
                optimal_mgae = counter;
            }
            
            if (alphaReeb_results[counter].mrms < best_mrms)
            {
                best_mrms = alphaReeb_results[counter].mrms;
                optimal_mrms = counter;
            }
        }
        
        alphaReeb_results[optimal_Betti].mean_time = alphaReeb_results[optimal_Betti].time / (double)input.repetitions;
        
        string result_file = result_directory + "AlphaReeb/List_Of_Results/AlphaReeb_hex.txt";
        
        ofstream ofs( result_file, ios::app );
        
        ofs << left << setw( 11 ) << input.pattern_type;
        ofs << left << setw( 7 ) << input.pattern_size_1;
        ofs << left << setw( 7 ) << input.pattern_size_2;
        ofs << left << setw( 5 ) << input.regular;
        ofs << left << setw( 9 ) << mean_cloud_size;
        ofs << left << setw( 12 ) << input.noise_type;
        ofs << left << setw( 13 ) << input.noise_parameter;
        ofs << left << setw( 12 ) << input.repetitions;
        ofs << left << setw( 11 ) << "AlphaReeb";
        ofs << left << setw( 6 ) << input.alphaReeb_simp_type;
        ofs << left << setw( 13 ) << alphaReeb_results[optimal_Betti].Betti_success_rate;
        ofs << left << setw( 13 ) << alphaReeb_results[optimal_homeo].homeo_success_rate;
        ofs << left << setw( 11 ) << alphaReeb_results[optimal_mgae].mgae;
        ofs << left << setw( 12 ) << alphaReeb_results[optimal_mrms].mrms;
        ofs << left << setw( 5 ) << alphaReeb_results[optimal_Betti].parameter_1;
        ofs << left << setw( 6 ) << "N/A";
        ofs << left << setw( 5 ) << alphaReeb_results[optimal_homeo].parameter_1;
        ofs << left << setw( 6 ) << "N/A";
        ofs << left << setw( 5 ) << alphaReeb_results[optimal_mgae].parameter_1;
        ofs << left << setw( 6 ) << "N/A";
        ofs << left << setw( 5 ) << alphaReeb_results[optimal_mrms].parameter_1;
        ofs << left << setw( 6 ) << "N/A";
        ofs << left << setw( 8 ) << alphaReeb_results[optimal_Betti].mean_time << endl;
        
        ofs.close();
    }
    
    if (input.hopes)
    {
        int Betti_successes = 0, homeo_successes = 0;
        double gae = 0, rms = 0;
        
        for (auto r : hopes_results.Betti_success) if (r) ++Betti_successes;
        
        for (auto r : hopes_results.homeo_success) if (r) ++homeo_successes;
        
        for (auto r : hopes_results.geom_approx_error) gae += r;
        
        for (auto r : hopes_results.rms) rms += r;
        
        hopes_results.Betti_success_rate = 100 * Betti_successes / (double)hopes_results.Betti_success.size();
        
        if (hopes_results.homeo_success.size() > 0) hopes_results.homeo_success_rate = 100 * homeo_successes / (double)hopes_results.homeo_success.size();
        else hopes_results.homeo_success_rate = 0;
        
        if (hopes_results.geom_approx_error.size() > 0) hopes_results.mgae = gae / (double)hopes_results.geom_approx_error.size();
        else hopes_results.mgae = 1e10;
        
        if (hopes_results.rms.size() > 0) hopes_results.mrms = rms / (double)hopes_results.rms.size();
        else hopes_results.mrms = 1e10;
        
        hopes_results.mean_time = hopes_results.time / (double)input.repetitions;
        
        string result_file = result_directory + "HoPeS/List_Of_Results/Hopes_hex.txt";

        ofstream ofs( result_file, ios::app );
        
        ofs << left << setw( 11 ) << input.pattern_type;
        ofs << left << setw( 7 ) << input.pattern_size_1;
        ofs << left << setw( 7 ) << input.pattern_size_2;
        ofs << left << setw( 5 ) << input.regular;
        ofs << left << setw( 9 ) << mean_cloud_size;
        ofs << left << setw( 12 ) << input.noise_type;
        ofs << left << setw( 13 ) << input.noise_parameter;
        ofs << left << setw( 12 ) << input.repetitions;
        ofs << left << setw( 11 ) << "HoPeS";
        ofs << left << setw( 6 ) << input.hopes_simp_type;
        ofs << left << setw( 13 ) << hopes_results.Betti_success_rate;
        ofs << left << setw( 13 ) << hopes_results.homeo_success_rate;
        ofs << left << setw( 11 ) << hopes_results.mgae;
        ofs << left << setw( 12 ) << hopes_results.mrms;
        ofs << left << setw( 5 ) << "N/A";
        ofs << left << setw( 6 ) << "N/A";
        ofs << left << setw( 5 ) << "N/A";
        ofs << left << setw( 6 ) << "N/A";
        ofs << left << setw( 5 ) << "N/A";
        ofs << left << setw( 6 ) << "N/A";
        ofs << left << setw( 5 ) << "N/A";
        ofs << left << setw( 6 ) << "N/A";
        ofs << left << setw( 8 ) << hopes_results.mean_time << endl;
        
        ofs.close();
    }
}
