#pragma once

class Life
{
    public:
    
    int index;
    double birth, death, span;
    int edge; // Index of critical edge in DelEdges.
    
    Life ( int i, double b, double d, int e );
    
    Life();
    ~Life();
};
