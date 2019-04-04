#pragma once

#include <iomanip>
#include <fstream>

#include <boost/filesystem.hpp>

#include "Graph.h"
#include "Directory.h"
#include "File_Name.h"

void Write_Graph ( string const& graph_directory, Input const& input, int expected_Betti_num, double graph_length, string const& algorithm, int iteration, Graph const& g )
{
    string directory;
    
    Directory( graph_directory, input, algorithm, directory );
    
    if (!boost::filesystem::is_directory( directory ))
    {
        boost::filesystem::create_directories( directory );
    }
    
	string graph_file;
    
	File_Name( directory, input, algorithm, iteration, ".txt", graph_file );

	ofstream ofs( graph_file );

    ofs << "Pattern_Type Pattern_Size_1 Pattern_Size_2 Graph_Dependent_Cloud_Size Cloud_Size_Parameter Noise_Type Noise_Parameter Original_Betti_Number Graph_Length" << endl;
    
    ofs << left << setw( 13 ) << input.pattern_type << setw( 15 ) << input.pattern_size_1 << setw( 15 ) << input.pattern_size_2 << setw( 27 ) << input.graph_dependent_cloud_size << setw( 21 ) << input.cloud_size_parameter << setw( 11 ) << input.noise_type << setw( 16 ) << input.noise_parameter << setw( 22 ) << expected_Betti_num << setw( 13 ) << graph_length << endl << endl;
    
	size_t num_vertices = boost::num_vertices( g );

    ofs << "Num_Vertices: " << num_vertices << "." << endl << endl;
    
    ofs << "Points (x, y):" << endl << endl;

	for (auto VertexPair = boost::vertices( g ); VertexPair.first != VertexPair.second; ++VertexPair.first)
	{
		ofs << g[*VertexPair.first].pt.x << " " << g[*VertexPair.first].pt.y << endl;
	}
    
    ofs << endl << "Edges:" << endl << endl;

	for (auto EdgePair = boost::edges( g ); EdgePair.first != EdgePair.second; ++EdgePair.first)
	{
		Graph::vertex_descriptor s, t;

		s = source( *EdgePair.first, g );
		t = target( *EdgePair.first, g );

		ofs << s << " " << t << endl;
	}
    
    ofs.close();
}
