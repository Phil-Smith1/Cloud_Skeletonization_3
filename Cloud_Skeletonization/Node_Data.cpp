#include "Node_Data.h"

Node_Data::Node_Data ()
{
    index = 0;  // Index in faces: 0 means external boundary.
    uplink = 0; // Index of the parent node in faces.
    birth = 0;
    height = 1; // No nodes below the new node.
    bar = -1;
    live.clear();
    edges.resize( 3 );
}

Node_Data::~Node_Data(){}
