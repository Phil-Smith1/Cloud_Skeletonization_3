#pragma once

#include <string>
#include <fstream>

using namespace std;

void Write_Results ( string const& BSD_directory, double& mapper_rms_error, double& aR_rms_error, double& hopes_rms_error, int iterations, int skip )
{
    mapper_rms_error = mapper_rms_error / (double)(iterations - skip);
    aR_rms_error = aR_rms_error / (double)(iterations - skip);
    hopes_rms_error = hopes_rms_error / (double)(iterations - skip);
    
    ofstream ofs( BSD_directory + "Results/Results.txt" );
    
    ofs << "The RMS error of the three algorithms over " << iterations - skip << " images from the BSDS500 database:" << endl << endl;
    ofs << "Mapper: " << mapper_rms_error << "." << endl;
    ofs << "Alpha-Reeb: " << aR_rms_error << "." << endl;
    ofs << "HoPeS: " << hopes_rms_error << "." << endl;
    
    ofs.close();
}
