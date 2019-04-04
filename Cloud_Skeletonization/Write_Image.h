#pragma once

#include <boost/filesystem.hpp>

#include "Directory.h"
#include "File_Name.h"

void Write_Image ( string const& image_directory, Input const& input, string const& algorithm, int iteration, Mat const& image )
{
    string directory;
    
    Directory( image_directory, input, algorithm, directory );
    
    if (!boost::filesystem::is_directory( directory ))
    {
        boost::filesystem::create_directories( directory );
    }
    
	string image_file;
    
	File_Name( directory, input, algorithm, iteration, ".png", image_file );
    
    imwrite( image_file, image );
}
