#pragma once

#include "Input.h"
#include "Num_To_String.h"

void File_Name ( string const& directory, Input const& input, string const& algorithm, int iteration, string const& ext, string& file_name )
{
    if (input.pattern_type == "grid")
    {
        file_name = directory + "/" + input.pattern_type + Num_To_String(input.pattern_size_1 ) + "," + Num_To_String(input.pattern_size_2 ) + "_" + input.noise_type + Num_To_String( input.noise_parameter ) + "_cloud" + Num_To_String_2( iteration + 1 ) + "_" + algorithm;
    }
    
    else
    {
        file_name = directory + "/" + input.pattern_type + Num_To_String(input.pattern_size_1 ) + "_" + input.noise_type + Num_To_String( input.noise_parameter ) + "_cloud" + Num_To_String_2( iteration + 1 ) + "_" + algorithm;
    }
    
    if (algorithm == "Mapper")
    {
        file_name += Num_To_String( input.num_intervals_param );
    }
    
    else if (algorithm == "AlphaReeb")
    {
        file_name += Num_To_String( input.alpha );
    }
    
    file_name += ext;
}
