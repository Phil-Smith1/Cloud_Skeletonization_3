#pragma once

#include <string>
#include <fstream>

using namespace std;

void Write_Results ( string const& BSD_directory, double& mapper_rms_error, double& aR_rms_error, double& hopes_rms_error, double& mapper_max_error, double& aR_max_error, double& hopes_max_error, double& mapper_time, double& aR_time, double& hopes_time, int iterations, int skip )
{
    mapper_rms_error = mapper_rms_error / (double)(iterations - skip);
    aR_rms_error = aR_rms_error / (double)(iterations - skip);
    hopes_rms_error = hopes_rms_error / (double)(iterations - skip);
    mapper_max_error = mapper_max_error / (double)(iterations - skip);
    aR_max_error = aR_max_error / (double)(iterations - skip);
    hopes_max_error = hopes_max_error / (double)(iterations - skip);
    mapper_time = mapper_time / (double)(iterations - skip);
    aR_time = aR_time / (double)(iterations - skip);
    hopes_time = hopes_time / (double)(iterations - skip);
    
    ofstream ofs( BSD_directory + "Results/Results.txt" );
    
    ofs << "The RMS error of the three algorithms over " << iterations - skip << " images from the BSDS500 database:" << endl << endl;
    ofs << "Mapper: " << mapper_rms_error << "." << endl;
    ofs << "Alpha-Reeb: " << aR_rms_error << "." << endl;
    ofs << "HoPeS: " << hopes_rms_error << "." << endl << endl;
    
    ofs << "The max error of the three algorithms over " << iterations - skip << " images from the BSDS500 database:" << endl << endl;
    ofs << "Mapper: " << mapper_max_error << "." << endl;
    ofs << "Alpha-Reeb: " << aR_max_error << "." << endl;
    ofs << "HoPeS: " << hopes_max_error << "." << endl << endl;
    
    ofs << "The mean time of the three algorithms over " << iterations - skip << " images from the BSDS500 database:" << endl << endl;
    ofs << "Mapper: " << mapper_time << "." << endl;
    ofs << "Alpha-Reeb: " << aR_time << "." << endl;
    ofs << "HoPeS: " << hopes_time << "." << endl;
    
    ofs.close();
}
