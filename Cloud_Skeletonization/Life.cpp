#include "Life.h"

Life::Life ( int i, double b, double d, int e )
{
    index = i;
    birth = b;
    death = d;
    span = d - b;
    edge = e;
}

Life::Life(){}

Life::~Life(){}
