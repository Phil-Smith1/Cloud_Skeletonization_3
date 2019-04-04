#pragma once

#include <fstream>
#include <sstream>

#include "Data_Pt.h"
#include "Cloud_File_Name.h"

void Read_Cloud ( string const& cloud_directory, Input const& input, int iteration, int& expected_Betti_num, double& graph_length, string& diagonal_edges, vector<Data_Pt>& cloud )
{
    string cloud_file_name;
    
    Cloud_File_Name( cloud_directory, input, iteration, cloud_file_name ); // Finding the cloud file.
    
    ifstream ifs( cloud_file_name );
    
    double x, y;
    string line_data, a, b, c, d, e, f, g;
    stringstream stream;
    
    getline( ifs, line_data );
    getline( ifs, line_data );
    
    stream << line_data;
    stream >> a >> b >> c >> d >> e >> f >> g >> expected_Betti_num >> graph_length >> diagonal_edges;
    
    getline( ifs, line_data );
    getline( ifs, line_data );
    getline( ifs, line_data );
    
    while (getline( ifs, line_data ))
    {
        stream.clear();
        stream << line_data;
        
        if (stream >> x >> y)
        {
            cloud.push_back( Data_Pt( Point2d( x, y ) ) ); // Extracting the cloud from the file.
        }
    }
    
    size_t c_s = cloud.size();
    
    for (int counter = 0; counter < c_s; ++counter)
    {
        cloud[counter].index = counter; // Allocating each point in the cloud an index.
    }
}
