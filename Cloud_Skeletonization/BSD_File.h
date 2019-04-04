#pragma once

#include <boost/filesystem.hpp>

#include <string>

using namespace std;

bool BSD_File ( int iteration, string const& test_directory, int test_directory_size, string const& train_directory, int train_directory_size, string const& val_directory, int val_directory_size, string& image_file )
{
    bool file_found = false;
    
    if (iteration < test_directory_size)
    {
        int counter = 0;
        
        for (auto & p : boost::filesystem::directory_iterator( test_directory ))
        {
            if (iteration == counter)
            {
                image_file = p.path().string();
                
                string str_end = &image_file.back() - 2;
                
                if (str_end != "jpg") break;
                
                file_found = true;
                
                break;
            }
            
            ++counter;
        }
    }
    
    else if (iteration < test_directory_size + train_directory_size)
    {
        int counter = test_directory_size;
        
        for (auto & p : boost::filesystem::directory_iterator( train_directory ))
        {
            if (iteration == counter)
            {
                image_file = p.path().string();
                
                string str_end = &image_file.back() - 2;
                
                if (str_end != "jpg") break;
                
                file_found = true;
                
                break;
            }
            
            ++counter;
        }
    }
    
    else
    {
        int counter = test_directory_size + train_directory_size;
        
        for (auto & p : boost::filesystem::directory_iterator( val_directory ))
        {
            if (iteration == counter)
            {
                image_file = p.path().string();
                
                string str_end = &image_file.back() - 2;
                
                if (str_end != "jpg") break;
                
                file_found = true;
                
                break;
            }
            
            ++counter;
        }
    }
    
    return file_found;
}
