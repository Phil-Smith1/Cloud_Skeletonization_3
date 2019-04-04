#pragma once

int Factorial ( int n )
{
    int factorial = 1;
    
    for (int counter = 2; counter <= n; ++counter)
    {
        factorial *= counter;
    }
    
    return factorial;
}
