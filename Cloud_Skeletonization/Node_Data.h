#pragma once

#include <vector>

using namespace std;

class Node_Data
{
    public:
    
    int index; // Index of triangle in faces.
    int uplink;
    double birth;
    int height; // Height of the tree rooted at Node.
    int bar; // Index of the region containing the triangle of this node.
    vector<int> live; // Indices of live triangles from Tree of this node.
    vector<int> edges; // Indices of edges of the corresponding triangle in DelEdges.
    
    Node_Data();
    
    ~Node_Data();
};
