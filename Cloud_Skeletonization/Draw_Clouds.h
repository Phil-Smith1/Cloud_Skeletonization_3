#pragma once

#include <opencv2/imgproc/imgproc.hpp>

#include "Scaling_Parameters.h"

void Draw_Clouds ( vector<vector<Data_Pt>>const& clouds, Mat& image )
{
    Point image_sizes = Point( image.cols, image.rows );
    double scale;
    Point2d shift;
    
    Scaling_Parameters( clouds, image_sizes, scale, shift );
    
    for (auto c : clouds)
    {
        for (auto p : c)
        {
            circle( image, Point( scale * p.pt + shift ), 2, CV_RGB( 0, 0, 0 ), -1 );
        }
    }
}
