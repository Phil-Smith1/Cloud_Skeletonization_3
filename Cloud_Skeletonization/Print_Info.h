#pragma once

#include <iostream>

void Print_Summary ( clock_t start_time, int experiment_iter )
{
    clock_t end_time = clock();
    double elapsed_time = (end_time - start_time) / (double)(CLOCKS_PER_SEC);
    double mean_experiment_time = elapsed_time / (double)experiment_iter;
    
    cout << endl;
    cout << "Summary:" << endl;
    cout << "  Code duration: " << elapsed_time << "s." << endl;
    cout << "  Number of experiments: " << experiment_iter << "." << endl;
    cout << "  Mean experiment time: " << mean_experiment_time << "s." << endl << endl;
}
