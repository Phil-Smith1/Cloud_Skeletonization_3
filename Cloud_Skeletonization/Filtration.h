#pragma once

#include "Edge.h"
#include "Life.h"
#include "Region.h"

#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

typedef DT::Vertex_iterator VI;
typedef DT::Finite_edges_iterator FEI;
typedef DT::Finite_faces_iterator FFI;

class Filtration
{
    public:
    
    DT delaunay;
    std::vector<FH> faces;
    std::vector<Edge> edges;
    std::vector<Life> persistence;
    std::vector<Region> map;
    std::vector<int> negative_edges;
    std::vector<int> positive_edges;
    
    static bool DecreasingLengths ( Edge const& e1, Edge const& e2 );
    
    int FindRoot ( int node, vector<FH>const& faces );
    
    bool is_acute ( K::Triangle_2 const& Triangle, double& radius );
    
    Filtration ( vector<P2>const& cloud );
    
    void Persistence1d ();
    
    Filtration();
    ~Filtration();
};
