#pragma once

#include "Node_Data.h"

#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> VB;
typedef CGAL::Triangulation_face_base_with_info_2<Node_Data, K> FB;
typedef CGAL::Triangulation_data_structure_2<VB, FB> TDS;
typedef CGAL::Delaunay_triangulation_2<K, TDS> DT;
typedef DT::Edge DE;
typedef DT::Vertex_handle VH;
typedef DT::Face_handle FH;
typedef K::Point_2 P2;
typedef K::Line_2 L2;

class Edge
{
    public:
    
    DE edge;
    VH end1, end2;
    int index, face1, face2, region1, region2;
    double length;
    
    pair<VH, VH> Vertices ( DE const& e );
    
    pair<FH, FH> Faces ( DE const& e );
    
    double SquaredLength ( DE const& e );
    
    Edge ( DE const& e, int i );
    
    Edge();
    
    ~Edge();
    
    void UpdateLength ();
};
