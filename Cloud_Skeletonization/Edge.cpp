#include "Edge.h"

pair<VH, VH> Edge::Vertices ( DE const& e )
{
    VH v1 = e.first -> vertex ( (e.second + 1) % 3 );
    VH v2 = e.first -> vertex ( (e.second + 2) % 3 );
    return make_pair( v1, v2 );
}

pair<FH, FH> Edge::Faces ( DE const& e )
{
    FH f1 = e.first;
    FH f2 = e.first->neighbor( e.second );
    return std::make_pair( f1, f2 );
}

double Edge::SquaredLength ( DE const& e )
{
    VH v1 = Vertices( e ).first;
    VH v2 = Vertices( e ).second;
    return squared_distance( v1->point(), v2->point() );
}

Edge::Edge ( DE const& e, int i )
{
    index = i;
    edge = e;
    pair<VH, VH> ends = Vertices( e );
    end1 = ends.first;
    end2 = ends.second;
    pair<FH, FH> faces = Faces( e );
    FH face = faces.first;
    region1 = face1 = face->info().index;
    face = faces.second;
    region2 = face2 = face->info().index;
    length = sqrt( SquaredLength( e ) );
}

Edge::Edge(){}

Edge::~Edge(){}

void Edge::UpdateLength ()
{
    length = sqrt( squared_distance( end1->point(), end2->point() ) );
}
