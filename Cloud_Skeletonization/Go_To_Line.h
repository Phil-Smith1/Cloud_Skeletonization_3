#pragma once

#include <fstream>
#include <string>

using namespace std;

void Go_To_Line ( ifstream& ifs, int line )
{
    string line_data;
    
    for (int counter = 1; counter < line; ++counter)
    {
        getline( ifs, line_data );
    }
}
