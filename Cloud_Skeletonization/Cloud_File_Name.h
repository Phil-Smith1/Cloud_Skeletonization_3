#pragma once

#include <boost/filesystem.hpp>

#include "Input.h"
#include "Num_To_String.h"

void Cloud_File_Name ( string const& directory, Input const& input, int iteration, string& file_name )
{
    file_name = directory + "Graph_Dependent_Cloud_Size/" + Num_To_String( input.cloud_size_parameter ) + "/" + input.noise_type + "/" + Num_To_String( input.noise_parameter ) + "/";
        
    if (input.pattern_type == "grid")
    {
        if (input.regular)
        {
            file_name += input.pattern_type + "/Regular/" + Num_To_String( input.pattern_size_1 ) + "," + Num_To_String( input.pattern_size_2 ) + "/" + input.pattern_type + Num_To_String( input.pattern_size_1 ) + "," + Num_To_String( input.pattern_size_2 ) + "_" + input.noise_type + Num_To_String( input.noise_parameter ) + "_cloud" + Num_To_String_2( iteration + 1 ) + ".txt";
        }
        
        else
        {
            file_name += input.pattern_type + "/Varied/" + Num_To_String( input.pattern_size_1 ) + "," + Num_To_String( input.pattern_size_2 ) + "/" + input.pattern_type + Num_To_String( input.pattern_size_1 ) + "," + Num_To_String( input.pattern_size_2 ) + "_" + input.noise_type + Num_To_String( input.noise_parameter ) + "_cloud" + Num_To_String_2( iteration + 1 ) + ".txt";
        }
    }
    
    else
    {
        file_name += input.pattern_type + "/" + Num_To_String( input.pattern_size_1 ) + "/" + input.pattern_type + Num_To_String( input.pattern_size_1 ) + "_" + input.noise_type + Num_To_String( input.noise_parameter ) + "_cloud" + Num_To_String_2( iteration + 1 ) + ".txt";
    }
}
