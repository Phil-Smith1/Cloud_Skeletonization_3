#pragma once

#include <opencv2/imgproc/imgproc.hpp>

#include "Edge.h"

using namespace cv;

class Graph_H
{
    public:
    
    int num_crit_edges = 0;
    vector<P2> vertices;
    vector<pair<int, int>> edges; // Pairs of indices of vertices.
    vector<double> edgelengths;
    vector<vector<int>> wedges; // Indices of edges around a vertex.
    vector<vector<P2>> chains; // Degree 2 vertices along a polygonal edge.
    vector<double> depth;
    
    Graph_H ( vector<Edge>const& DelEdges, vector<int>const& EdgeIndices, int nVertices );
    
    void Initialise_Graph ( vector<Edge>const& DelEdges, vector<int>const& EdgeIndices, int nVertices );
    
    Point ScaleShift ( P2 p, double scale, Point2d shift );
    
    void DrawEdge ( P2 v1, P2 v2, double scale, Point2d shift, CvScalar color, int thickness, Mat& image );
    
    void Draw (double scale, Point2d shift, Scalar color, Scalar crit_color, int thick, Mat& image);
    
    Graph_H();
    ~Graph_H();
};
