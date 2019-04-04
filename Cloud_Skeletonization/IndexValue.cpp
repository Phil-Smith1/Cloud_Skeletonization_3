#include "IndexValue.h"

IndexValue::IndexValue ( int i, double v )
{
    index = i;
    value = v;
}

IndexValue::IndexValue ()
{
    value = 0;
}

IndexValue::~IndexValue(){}
