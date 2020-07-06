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
    
    double scale = 650 / (double)death_max;
    Point2d shift = Point2d( 75, 75 );
    
    putText( image, "Birth", ScaleShift( Point2d( death_max - 0.03, death_max + 0.02 ), scale, shift ), 1, 3, CV_RGB( 0, 0, 0 ), 2 );
    
    putText( image, "Death", ScaleShift( Point2d( -0.02, -0.01 ), scale, shift ), 1, 3, CV_RGB( 0, 0, 0 ), 2 );
    
    size_t num_dots = Persistence.size();
    
    Point pts[1][4] = {};
    
    pts[0][0] = ScaleShift( Point2d( 0, death_max - (Persistence[index_above_gap - 1].death - Persistence[index_above_gap - 1].birth) ), scale, shift );
    pts[0][1] = ScaleShift( Point2d( 0, death_max - (Persistence[index_above_gap].death - Persistence[index_above_gap].birth) ), scale, shift );
    pts[0][2] = ScaleShift( Point2d( death_max - (Persistence[index_above_gap].death - Persistence[index_above_gap].birth), 0 ), scale, shift );
    pts[0][3] = ScaleShift( Point2d( death_max - (Persistence[index_above_gap - 1].death - Persistence[index_above_gap - 1].birth), 0 ), scale, shift );
    
    const Point* ppt[1] = { pts[0] };
    int npt[] = { 4 };
    
    fillPoly( image, ppt, npt, 1, CV_RGB( 255, 255, 0 ) );
    
    for (int counter = 0; counter < num_dots; ++counter)
    {
        Point2d p( Persistence[counter].birth, death_max - Persistence[counter].death );
        
        int size = 4;
        if (counter < index_above_gap) size = 2;
        
        circle( image, ScaleShift( p, scale, shift ), size, CV_RGB( 255, 0, 0 ), -1 );
    }
    
    arrowedLine( image, ScaleShift( Point2d( 0, death_max ), scale, shift ), ScaleShift( Point2d( 0, 0 ), scale, shift ), CV_RGB( 0, 0, 0 ), 2, 8, 0, 0.02 );
    arrowedLine( image, ScaleShift( Point2d( 0, death_max ), scale, shift ), ScaleShift( Point2d( death_max, death_max ), scale, shift ), CV_RGB( 0, 0, 0 ), 2, 8, 0, 0.02 );
    line( image, ScaleShift( Point2d( 0, death_max ), scale, shift ), ScaleShift( Point2d( death_max, 0 ), scale, shift ), CV_RGB( 0, 0, 0 ), 2 );
}
