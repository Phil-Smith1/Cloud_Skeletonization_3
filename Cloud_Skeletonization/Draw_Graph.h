#pragma once

#include <opencv2/imgproc/imgproc.hpp>

#include "Scaling_Parameters.h"
#include "Filtration.h"

void Draw_Vertices ( Graph const& g, double scale, Point2d& shift, int radius_vertices, bool fill, Scalar const& colour, Mat& image )
{
	int thickness = 1;
	if (fill) thickness = -1;

	pair<vertex_iter, vertex_iter> VertexPair;
    
	for (VertexPair = boost::vertices( g ); VertexPair.first != VertexPair.second; ++VertexPair.first)
	{
		circle( image, Point(scale * g[*VertexPair.first].pt + shift), radius_vertices, colour, thickness );
	}
}

void Draw_Edges ( Graph const& g, double scale, Point2d& shift, int thickness_edge, Scalar const& colour, Mat& image )
{
    for (auto ei = boost::edges( g ).first; ei != boost::edges( g ).second; ++ei)
	{
        int parallel_counter = 0;
        
        for (auto oei = boost::out_edges( boost::source( *ei, g ), g ).first; oei != boost::out_edges( boost::source( *ei, g), g ).second; ++oei)
        {
            if (boost::target( *oei, g ) == boost::target( *ei, g )) ++parallel_counter;
        }
        
        if (true)
        {
            line( image, Point( scale * g[boost::source( *ei, g )].pt + shift ), Point( scale * g[boost::target( *ei, g )].pt + shift ), colour, thickness_edge );
        }
        
        if (false)
        {
            Point v = Point( scale * g[boost::target( *ei, g )].pt + shift ) - Point( scale * g[boost::source( *ei, g )].pt + shift );
            double n = norm ( v );
            
            circle( image, Point( scale * g[boost::source( *ei, g )].pt + shift ) + v / 2, n / 2, colour, thickness_edge );
        }
	}
}

void Draw_Graph ( Graph const& g, double scale, Point2d shift, int radius_vertices, bool fill, int thickness_edge, Scalar const& colour, Mat& image )
{
    Draw_Vertices( g, scale, shift, radius_vertices, fill, colour, image );
    
    Draw_Edges( g, scale, shift, thickness_edge, colour, image );
}

void Draw_Graph ( Graph const& g, int radius_vertices, bool fill, int thickness_edge, Scalar const& colour, Mat& image )
{
    Point image_sizes( image.cols, image.rows );
    double scale;
    Point2d shift;
    
    Scaling_Parameters( g, image_sizes, scale, shift );
    
	Draw_Vertices( g, scale, shift, radius_vertices, fill, colour, image );

	Draw_Edges( g, scale, shift, thickness_edge, colour, image );
}

void Draw_Graph ( Graph_H& g, Scalar const& colour_1, Scalar const& colour_2, Mat& image )
{
    Point image_sizes( image.cols, image.rows );
    double scale;
    Point2d shift;
    
    Scaling_Parameters( g, image_sizes, scale, shift );
    
    g.Draw( scale, shift, colour_1, colour_2, 1, image );
}
