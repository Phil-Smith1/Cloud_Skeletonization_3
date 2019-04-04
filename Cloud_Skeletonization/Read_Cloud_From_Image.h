#pragma once

#include "Single_Edge_Clustering.h"
#include "Convert_Cloud.h"

void Canny_Detector ( Mat const& input_image, int low_threshold, double ratio, Mat& Canny_edges )
{
    int size_kernel = 3;
    Mat edges_image;
    
    blur( input_image, edges_image, Size( 3, 3 ) );
    
    Canny( edges_image, Canny_edges, low_threshold, ratio * low_threshold, size_kernel );
}

void Load_Cloud ( Mat const& image_cloud, vector<P2>& cloud )
{
    for (int j = 0; j < image_cloud.rows; ++j)
    {
        for (int i = 0; i < image_cloud.cols; ++i)
        {
            if (image_cloud.at<uchar>( j, i ) != 0) cloud.push_back( P2( i, j ) );
        }
    }
}

void Read_Cloud_From_Image ( string const& image_directory, string const& image_name, Mat const& input_image, vector<P2>& cloud_p, vector<vector<P2>>& clouds_p, vector<vector<Data_Pt>>& clouds_d )
{
    int Canny_low_threshold = 75;
    double Canny_ratio = 3;
    Mat Canny_edges;
    
    Canny_Detector( input_image, Canny_low_threshold, Canny_ratio, Canny_edges );
    
    Load_Cloud( Canny_edges, cloud_p );
    
    clouds_p.assign( 1, cloud_p );
    
    Single_Edge_Clustering( 3, clouds_p );
    
    clouds_d.resize( clouds_p.size() );
    
    for (int counter = 0; counter < clouds_p.size(); ++counter)
    {
        Convert_Cloud_2( clouds_p[counter], clouds_d[counter] );
    }
    
    Mat dst;
    
    Canny_edges.copyTo( dst );
    
    cvtColor( dst, dst, COLOR_GRAY2BGR );
    
    for (int y = 0; y < dst.rows; ++y)
    {
        for (int x = 0; x < dst.cols; ++x)
        {
            if (dst.at<Vec3b>( Point( x,y ) )[0] > 10)
            {
                dst.at<Vec3b>( Point( x,y ) )[0] = dst.at<Vec3b>( Point( x,y ) )[1] = 0;
            }
            
            else dst.at<Vec3b>( Point( x,y ) )[0] = dst.at<Vec3b>( Point( x,y ) )[1] = dst.at<Vec3b>( Point( x,y ) )[2] = 255;
        }
    }
    
    for (int y = 0; y < dst.rows; ++y)
    {
        for (int x = 0; x < dst.cols; ++x)
        {
            if (dst.at<Vec3b>( Point( x,y ) )[0] > 10)
            {
                dst.at<Vec3b>( Point( x,y ) ) = input_image.at<Vec3b>( Point( x, y ) );
            }
        }
    }
    
    imwrite( image_directory + "Edges_On_" + image_name + ".png", dst );
}

void Read_Cloud_From_Image ( Mat const& input_image, vector<P2>& cloud_p, vector<vector<P2>>& clouds_p, vector<vector<Data_Pt>>& clouds_d )
{
    int Canny_low_threshold = 75;
    double Canny_ratio = 3;
    Mat Canny_edges;
    
    Canny_Detector( input_image, Canny_low_threshold, Canny_ratio, Canny_edges );
    
    Load_Cloud( Canny_edges, cloud_p );
    
    clouds_p.assign( 1, cloud_p );
    
    Single_Edge_Clustering( 3, clouds_p );
    
    clouds_d.resize( clouds_p.size() );
    
    for (int counter = 0; counter < clouds_p.size(); ++counter)
    {
        Convert_Cloud_2( clouds_p[counter], clouds_d[counter] );
    }
}
