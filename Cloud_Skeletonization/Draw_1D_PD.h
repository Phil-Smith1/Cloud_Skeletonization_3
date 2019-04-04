#pragma once

#include <opencv2/imgproc/imgproc.hpp>

#include "Life.h"

Point2d ScaleShift ( Point2d p, double scale, Point2d shift )
{
    return Point2d( scale * p.x + shift.x, scale * p.y + shift.y );
}

void Draw_1D_PD ( vector<Life>const& Persistence, int index_above_gap, Mat& image )
{
    double death_max = 0;
    
    for (auto it = Persistence.begin(); it != Persistence.end(); ++it)
    {
        if (it->death > death_max) death_max = it->death;
    }
    
    double scale = 600 / (double)death_max;
    Point2d shift = Point2d( 100, 100 );
    
    line( image, ScaleShift( Point2d( 0, death_max ), scale, shift ), ScaleShift( Point2d( 0, 0 ), scale, shift ), CV_RGB( 0, 0, 0 ), 1 );
    line( image, ScaleShift( Point2d( 0, death_max ), scale, shift ), ScaleShift( Point2d( death_max, death_max ), scale, shift ), CV_RGB( 0, 0, 0 ), 1 );
    line( image, ScaleShift( Point2d( 0, death_max ), scale, shift ), ScaleShift( Point2d( death_max, 0 ), scale, shift ), CV_RGB( 0, 0, 0 ), 1 );
    
    size_t num_dots = Persistence.size();
    
    for (int counter = 0; counter < num_dots; ++counter)
    {
        Point2d p( Persistence[counter].birth, death_max - Persistence[counter].death );
        
        int size = 4;
        if (counter < index_above_gap) size = 2;
        
        circle( image, ScaleShift( p, scale, shift ), size, CV_RGB( 0, 0, 0 ), -1 );
    }
}
