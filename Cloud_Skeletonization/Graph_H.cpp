#include "Graph_H.h"

Graph_H::Graph_H ( vector<Edge>const& DelEdges, vector<int>const& EdgeIndices, int nVertices )
{
    vertices.resize (nVertices);
    wedges.resize (nVertices);
    edges.resize( EdgeIndices.size() );
    edgelengths.resize( EdgeIndices.size() );
    
    for (int i = 0; i < EdgeIndices.size(); ++i)
    {
        Edge e = DelEdges[EdgeIndices[i]];
        edges[i].first = e.end1->info();
        edges[i].second = e.end2->info();
        edgelengths[i] = e.length;
        vertices[e.end1->info()] = e.end1->point();
        vertices[e.end2->info()] = e.end2->point();
        wedges[e.end1->info()].push_back( i );
        wedges[e.end2->info()].push_back( i );
    }
}

void Graph_H::Initialise_Graph ( vector<Edge>const& DelEdges, vector<int>const& EdgeIndices, int nVertices )
{
    vertices.resize (nVertices);
    wedges.resize (nVertices);
    edges.resize( EdgeIndices.size() );
    edgelengths.resize( EdgeIndices.size() );
    
    for (int i = 0; i < EdgeIndices.size(); ++i)
    {
        Edge e = DelEdges[EdgeIndices[i]];
        edges[i].first = e.end1->info();
        edges[i].second = e.end2->info();
        edgelengths[i] = e.length;
        vertices[e.end1->info()] = e.end1->point();
        vertices[e.end2->info()] = e.end2->point();
        wedges[e.end1->info()].push_back( i );
        wedges[e.end2->info()].push_back( i );
    }
}

Point Graph_H::ScaleShift ( P2 p, double scale, Point2d shift )
{
    return Point2i ( int( scale * p.x() + shift.x ), int( scale * p.y() + shift.y ) );
}

void Graph_H::DrawEdge ( P2 v1, P2 v2, double scale, Point2d shift, CvScalar color, int thickness, Mat& image )
{
    line( image, ScaleShift( v1, scale, shift ), ScaleShift( v2, scale, shift ), color, thickness );
}

void Graph_H::Draw (double scale, Point2d shift, Scalar color, Scalar crit_color, int thick, Mat& image)
{
    Scalar c = color;
    
    for (size_t e = 0; e < edges.size(); ++e)
    {
        if (e + 1 == (int)vertices.size()) c = crit_color;
        
        int v1 = edges[e].first, v2 = edges[e].second;
        P2 p1 = vertices[v1], p2 = vertices[v2];
        
        DrawEdge( p1, p2, scale, shift, c, 2 * thick, image );
    }
    
    for (size_t i = 0; i < vertices.size(); ++i)
    {
        circle( image, ScaleShift( vertices[i], scale, shift ), 2 * thick, CV_RGB( 0, 0, 0 ), -1 );
    }
}

Graph_H::Graph_H(){}
Graph_H::~Graph_H(){}
