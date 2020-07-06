// Cloud skeletonization project.

// Inclusions.

#include "Write_Input.h"
#include "Read_Input.h"
#include "Initialise_Results.h"
#include "Read_Cloud.h"
#include "Original_Pattern.h"
#include "Find_Epsilon.h"
#include "Cloud_To_Nbhd_Graph.h"
#include "Mapper.h"
#include "AlphaReeb_Algorithm.h"
#include "Hopes.h"
#include "Simplify_Graph.h"
#include "Simplify_HoPeS.h"
#include "Validation.h"
#include "Draw_Graph.h"
#include "Write_Image.h"
#include "Convert_Graph.h"
#include "Write_Graph.h"
#include "Analysis.h"
#include "Read_Cloud_From_Image.h"
#include "Draw_Clouds.h"
#include "Print_Info.h"
#include "BSD_File.h"
#include "Write_Results.h"

// Global variables.

const bool cloud_input = true; // Run algorithms over cloud dataset.

const vector<int> wheel_range = { 4/*3, 4, 5, 6, 7, 8, 9*/ };
const vector<int> grid_cols_range = { /*1, 2, 3, 4*/ };
const vector<int> grid_rows_range = { /*1, 2, 3, 4*/ };
const vector<int> triangles_range = { /*1, 2, 3, 4, 5, 6, 7, 8*/ };
const vector<int> hexagonal_range = { /*1, 2, 3, 4, 5 6, 7*/ };
const vector<int> squares_range = { /*2, 3, 4, 5, 6, 7, 8, 9*/ };

const bool regular = true; // All grid patterns are regular.

const bool graph_dependent_cloud_size = true; // Cloud size is dependent on the length of the pattern.
const int cloud_size_parameter = 100; // Number of points in the cloud per unit length of the pattern.

const string noise_type = "uniform"; // Type of noise used to produce the cloud: uniform or gaussian.
const vector<double> noise_parameter_range = { 0.1/*0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55 0.6, 0.65, 0.7, 0.75*/ /*0.02, 0.04, 0.06, 0.08, 0.1, 0.12, 0.14, 0.16, 0.18, 0.2 0.22, 0.24, 0.26 0.28, 0.3, 0.32*/ }; // Range of magnitude of noise.

const bool mapper = false; // Run the cloud through the Mapper algorithm.
const bool graph_dependent_num_intervals = true; // Number of intervals is dependent on the length of the pattern.
const vector<double> num_intervals_parameter = { 1.5, 1.7, 1.9, 2.1, 2.3, 2.5, 2.7, 2.9, 3.1, 3.3 }; // Range of the number of intervals parameter: number of intervals = parameter x pattern length.
const vector<double> DBSCAN_parameter = { 0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5 }; // Range of DBSCAN parameter.
const double overlap_ratio = 0.5; // Ratio of overlap of adjacent intervals.
const string filter_function = "Distance";
const double sigma = 0.1; // Used in the Gaussian density filter function.
const int mapper_simp_type = 1; // Type of simplication of the Mapper output: 0: No simplification; 1: RD1V.

const bool alphaReeb = false; // Run the cloud through the alpha-Reeb algorithm.
const vector<double> alpha_values = { 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6 }; // Range of alpha values.
const int alphaReeb_simp_type = 1; // Type of simplication of the alpha-Reeb output: 0: No simplification; 1: RD1V.

const double mcsf = 0.05; // A component must represent a fraction of points greater than this fraction to be included in the output.

const bool hopes = true; // Run the cloud through the HoPeS algorithm.
const int hopes_simp_type = 0; // Type of simplification of the HoPeS output: 0: No simplification; 1: RD1V; 2: RD1V SH MD; 3: RD1V SH 2MD; 4: aR RD1V; 5: RD1V aR RD1V; 6: SH2; 7: SH MD.

const int repetitions = 1; // Number of repetitions of the same type of cloud.

const bool validation = false; // Record the results.

const bool test = false; // To do a test run.

// If test: wr 3; gdcp true; csp 100; nt uniform; npr 0.05; av 0.3; e 0.1; gdni true; nip 1.4; mcsf 0.01; r 5; v false.

const bool image_input = false; // Run algorithms over an image.

const string image_name = "Woman"; // Woman, Bird_1, Bird_2, Bird_3, Plane, Pottery, Car, Kangaroo, Rock, Basket, Giraffe, Gull, Ostrich, Penguin, Man.

const bool BSD = false; // Run algorithms over the BSD database.

const bool mapper_on_image = true; // Run Mapper algorithm on images.

const bool alphaReeb_on_image = true; // Run alpha-Reeb algorithm on images.

const bool hopes_on_image = true; // Run HoPeS algorithm on images.

const int hopes_simp_type_2 = 0; // Type of simplification of the HoPeS output for images: 0: No simplification; 1: RD1V; 2: RD1V SH MD; 3: RD1V SH 2MD; 4: aR RD1V; 5: RD1V aR RD1V; 6: SH2; 7: SH MD.

Run_Input run_input( wheel_range, grid_cols_range, grid_rows_range, regular, triangles_range, hexagonal_range, squares_range, graph_dependent_cloud_size, cloud_size_parameter, noise_type, noise_parameter_range, mapper, mapper_simp_type, alphaReeb, alphaReeb_simp_type, hopes, hopes_simp_type, repetitions );

// Global constants.

const Scalar white = CV_RGB( 255, 255, 255 );
const Scalar black = CV_RGB( 0, 0, 0 );
const Scalar red = CV_RGB ( 255, 0, 0 );

// Directories.

const string root_directory = "/Users/philsmith/Documents/Xcode Projects/Cloud_Skeletonization/";
const string input_file = root_directory + "Input/Input.txt";
const string cloud_directory = root_directory + "Clouds/Txt_Files/";
const string image_directory = root_directory + "Code_Output/Images/";
const string graph_directory = root_directory + "Code_Output/Graphs/";
const string result_directory = root_directory + "Results/";
const string BSD_directory = root_directory + "BSDS500/";
const string BSD_image_directory = BSD_directory + image_name + "/";

int main ( int, char*[] )
{
    if (cloud_input) // Caries out algorithms on user-generated clouds.
    {
        clock_t start_time = clock(); // Start stopwatch.
        
        Write_Input( input_file, run_input ); // Writing input.
        
        int experiment_iter = 0; // Counter for the number of experiments performed.
        
        ifstream ifs( input_file );
        string line_data;
        getline( ifs, line_data );
        
        while (getline( ifs, line_data )) // Looping over lines in the input file.
        {
            ++experiment_iter;
            
            Input input;
            
            Read_Input( line_data, input ); // Reading the input.
            
            size_t cloud_size = 0;
            vector<Results> mapper_results( num_intervals_parameter.size() * DBSCAN_parameter.size() );
            vector<Results> alphaReeb_results( alpha_values.size() );
            Results hopes_results;
            
            Initialise_Results( mapper_results, num_intervals_parameter, DBSCAN_parameter, alphaReeb_results, alpha_values, hopes_results, input.repetitions );
            
            for (int iteration = 0; iteration < input.repetitions; ++iteration) // Looping over clouds.
            {
                int expected_Betti_num;
                double graph_length;
                string diagonal_edges;
                vector<Data_Pt> cloud_d;
                vector<P2> cloud_p;
                
                Read_Cloud( cloud_directory, input, iteration, expected_Betti_num, graph_length, diagonal_edges, cloud_d ); // Reading the cloud.
                
                cloud_size += cloud_d.size();
                
                Convert_Cloud_1( cloud_d, cloud_p ); // Creating a P2 cloud from a Data_Pt cloud.
                
                Graph original_pattern;
                
                Original_Pattern( input.pattern_type, input.pattern_size_1, input.pattern_size_2, diagonal_edges, original_pattern ); // Reconstructing the original pattern from which the cloud was produced.
                
                bool draw_image = iteration % 50 == 0 || test ? true : false; // Draw every fiftieth image.
                
                if (input.mapper) // Runs the cloud through the Mapper algorithm.
                {
                    for (int counter_1 = 0; counter_1 < num_intervals_parameter.size(); ++counter_1) // Looping over number of intervals;
                    {
                        for (int counter_2 = 0; counter_2 < DBSCAN_parameter.size(); ++counter_2) // Looping over DBSCAN parameter values.
                        {
                            input.graph_dependent_num_intervals = graph_dependent_num_intervals;
                            
                            if (input.graph_dependent_num_intervals)
                            {
                                input.num_intervals_param = num_intervals_parameter[counter_1];
                                input.num_intervals = input.num_intervals_param * graph_length + 0.5;
                            }
                            
                            else input.num_intervals = num_intervals_parameter[counter_1];
                            
                            input.DBSCAN_parameter = DBSCAN_parameter[counter_2];
                            
                            Mapper_Parameters parameters( input.num_intervals, overlap_ratio, filter_function, sigma, input.DBSCAN_parameter, mcsf );
                            
                            clock_t start_iter = clock(); // Start stopwatch for iteration.
                            
                            Graph mapper_graph;
                            
                            Mapper( cloud_d, parameters, mapper_graph ); // Generating the mapper graph.
                            
                            clock_t end_iter = clock(); // Stop stopwatch for iteration.
                            
                            mapper_results[counter_1 * DBSCAN_parameter.size() + counter_2].time += (end_iter - start_iter) * 1000 / (double)(CLOCKS_PER_SEC);
                            
                            Simplify_Graph( mapper_graph, mapper_simp_type ); // Simplifying the output.
                            
                            if (validation)
                            {
                                if (input.pattern_type == "hexagonal" && input.pattern_size_1 == 7)
                                {
                                    Validation_7Hex( expected_Betti_num, original_pattern, cloud_p, mapper_graph, mapper_results[counter_1 * DBSCAN_parameter.size() + counter_2] );
                                }
                                
                                else Validation( expected_Betti_num, original_pattern, cloud_p, mapper_graph, mapper_results[counter_1 * DBSCAN_parameter.size() + counter_2] ); // Testing Betti number, homeomorphism, geometric errors.
                            }
                            
                            if (draw_image)
                            {
                                const Point image_sizes( 800, 800 );
                                Mat image( image_sizes, CV_8UC3, white );
                                
                                Draw_Graph( mapper_graph, 5, -1, 2, black, image ); // Drawing the output graph.
                                
                                Write_Image( image_directory, input, "Mapper", iteration, image ); // Writing the image to a png file.
                                
                                Write_Graph( graph_directory, input, expected_Betti_num, graph_length, "Mapper", iteration, mapper_graph ); // Writing the graph to a txt file.
                            }
                        }
                    }
                }
                
                if (input.alphaReeb) // Runs the cloud through the alpha-Reeb algorithm.
                {
                    double epsilon;
                    
                    Find_Epsilon( cloud_p, epsilon ); // Epsilon is used to create a nbhd graph of the cloud, and is equal to twice the max birth of cycles above the widest gap in the PD.
                    
                    Graph nbhd_graph;
                    
                    Cloud_To_Nbhd_Graph( cloud_d, epsilon, nbhd_graph ); // Generating the neighbourhood graph of the cloud.
                    
                    for (int counter = 0; counter < alpha_values.size(); ++counter) // Looping over alpha values.
                    {
                        input.alpha = alpha_values[counter];
                        AlphaReeb_Parameters parameters( input.alpha, mcsf );
                        
                        clock_t start_iter = clock(); // Start stopwatch for iteration.
                        
                        Graph alphaReeb_graph;
                        
                        AlphaReeb_Algorithm( nbhd_graph, parameters, alphaReeb_graph ); // Alpha-Reeb algorithm.
                        
                        clock_t end_iter = clock(); // Stop stopwatch for iteration.
                        
                        alphaReeb_results[counter].time += (end_iter - start_iter) * 1000 / (double)(CLOCKS_PER_SEC);
                        
                        Simplify_Graph( alphaReeb_graph, alphaReeb_simp_type ); // Simplifying the output.
                        
                        if (validation)
                        {
                            if (input.pattern_type == "hexagonal" && input.pattern_size_1 == 7)
                            {
                                Validation_7Hex( expected_Betti_num, original_pattern, cloud_p, alphaReeb_graph, alphaReeb_results[counter] );
                            }
                            
                            else Validation( expected_Betti_num, original_pattern, cloud_p, alphaReeb_graph, alphaReeb_results[counter] ); // Testing Betti number, homeomorphism, geometric errors.
                        }
                        
                        if (draw_image)
                        {
                            const Point image_sizes( 800, 800 );
                            Mat image( image_sizes, CV_8UC3, white );
                            
                            Draw_Graph( alphaReeb_graph, 5, -1, 2, black, image ); // Drawing the output graph.
                            
                            Write_Image( image_directory, input, "AlphaReeb", iteration, image ); // Writing the image to a png file.
                            
                            Write_Graph( graph_directory, input, expected_Betti_num, graph_length, "AlphaReeb", iteration, alphaReeb_graph ); // Writing the graph to a txt file.
                        }
                    }
                }
                
                if (input.hopes) // Runs the cloud through the HoPeS algorithm.
                {
                    clock_t start_iter = clock(); // Start stopwatch for iteration.
                    
                    double max_birth = 0, min_death = 1e10;
                    Graph_H hopes_graph;
                    
                    Hopes( cloud_p, hopes_graph, max_birth, min_death, false ); // Generating the Hopes graph.
                    
                    clock_t end_iter = clock(); // Stop stopwatch for iteration.
                    
                    hopes_results.time += (end_iter - start_iter) * 1000 / (double)(CLOCKS_PER_SEC);
                    
                    Graph hopes;
                    
                    Simplify_Graph( hopes_graph, hopes_simp_type, min_death, mcsf, hopes ); // Simplifying the output.
                    
                    if (validation)
                    {
                        if (input.pattern_type == "hexagonal" && input.pattern_size_1 == 7)
                        {
                            Validation_7Hex( expected_Betti_num, original_pattern, cloud_p, hopes, hopes_results );
                        }
                        
                        else Validation( expected_Betti_num, original_pattern, cloud_p, hopes, hopes_results ); // Testing Betti number, homeomorphism, geometric errors.
                    }
                    
                    if (draw_image)
                    {
                        const Point image_sizes( 800, 800 );
                        Mat image( image_sizes, CV_8UC3, white );
                        
                        if (hopes_simp_type <= 1) Draw_Graph( hopes_graph, black, red, image ); // Drawing the output graph.
                        
                        else Draw_Graph( hopes, 5, -1, 2, black, image );
                                                    
                        Write_Image( image_directory, input, "HoPeS1", iteration, image ); // Writing the image to a png file.
                        
                        Write_Graph( graph_directory, input, expected_Betti_num, graph_length, "HoPeS1", iteration, hopes ); // Writing the graph to a txt file.
                    }
                }
                
                cout << "Experiment " << experiment_iter << ": Iteration " << iteration << "." << endl;
            }
            
            size_t mean_cloud_size = cloud_size / input.repetitions;
            
            if (validation) Analysis( result_directory, input, mean_cloud_size, mapper_results, alphaReeb_results, hopes_results ); // Writing results to a txt file.
        }
        
        Print_Summary( start_time, experiment_iter ); // Printing summary.
    }
    
    if (image_input)
    {
        Mat input_image;
        
        input_image = imread( BSD_image_directory + image_name + ".jpg" ); // Reading the image.

        vector<P2> cloud_p;
        vector<vector<P2>> clouds_p;
        vector<vector<Data_Pt>> clouds_d;
        
        Read_Cloud_From_Image( BSD_image_directory, image_name, input_image, cloud_p, clouds_p, clouds_d ); // Extracting the cloud from the image.
        
        const Point image_sizes( 4 * input_image.cols, 4 * input_image.rows );
        Mat cloud_image( image_sizes, CV_8UC3, white );
        
        double scale;
        Point2d shift;
        
        Scaling_Parameters( clouds_d, image_sizes, scale, shift );
        
        Draw_Clouds( clouds_d, cloud_image );
        
        imwrite( BSD_directory + image_name + "/" + image_name + "_Cloud.png", cloud_image ); // Writing the cloud to a png file.
        
        if (mapper_on_image) // Runs the image through the Mapper algorithm.
        {
            Mat mapper_image( image_sizes, CV_8UC3, white );
            vector<Graph> mapper_graph( clouds_p.size() );
            
            for (int counter = 0; counter < clouds_p.size(); ++counter) // Looping over clouds.
            {
                Mapper_Parameters parameters( 15, 0.5, "Distance", 0.1, 3, 0 );
                
                Mapper( clouds_d[counter], parameters, mapper_graph[counter] ); // Generating the mapper graph.
            }
            
            for (int counter = 0; counter < mapper_graph.size(); ++counter)
            {
                Draw_Graph( mapper_graph[counter], scale, shift, 2, -1, 2, black, mapper_image ); // Drawing the output graph.
            }
            
            imwrite( BSD_directory + image_name + "/" + image_name + "_Mapper.png", mapper_image ); // Writing the image to a png file.
            
            cout << "Completed mapper algorithm on " << image_name << "." << endl << endl;
        }
        
        if (alphaReeb_on_image) // Runs the image through the alpha-Reeb algorithm.
        {
            Mat alphaReeb_image( image_sizes, CV_8UC3, white );
            vector<Graph> alphaReeb_graph( clouds_p.size() );
            
            for (int counter = 0; counter < clouds_p.size(); ++counter) // Looping over clouds.
            {
                double epsilon;
                
                Find_Epsilon( clouds_p[counter], epsilon ); // Epsilon is used to create a nbhd graph of the cloud, and is equal to twice the max birth of cycles above the widest gap in the PD.
                
                Graph nbhd_graph;
                
                Cloud_To_Nbhd_Graph( clouds_d[counter], epsilon, nbhd_graph ); // Generating the neighbourhood graph of the cloud.
                
                AlphaReeb_Parameters parameters( 4, 0 );
                
                AlphaReeb_Algorithm( nbhd_graph, parameters, alphaReeb_graph[counter] ); // Alpha-Reeb algorithm.
            }
            
            for (int counter = 0; counter < alphaReeb_graph.size(); ++counter)
            {
                Draw_Graph( alphaReeb_graph[counter], scale, shift, 2, -1, 2, black, alphaReeb_image ); // Drawing the output graph.
            }
            
            imwrite( BSD_directory + image_name + "/" + image_name + "_AlphaReeb.png", alphaReeb_image ); // Writing the image to a png file.
            
            cout << "Completed alpha-Reeb algorithm on " << image_name << "." << endl << endl;
        }
        
        if (hopes_on_image) // Runs the image through the HoPeS algorithm.
        {
            Mat hopes_image( image_sizes, CV_8UC3, white );
            vector<Graph> hopes_graph( clouds_p.size() );
            
            for (int counter = 0; counter < clouds_p.size(); ++counter) // Looping over clouds.
            {
                double max_birth = 0, min_death = 1e10;
                Graph_H g;
                
                Hopes( clouds_p[counter], g, max_birth, min_death, false ); // Generating the Hopes graph.
                
                Simplify_Graph( g, hopes_simp_type_2, min_death, mcsf, hopes_graph[counter] ); // Simplifying the output.
                
                g.Draw( scale, shift, CV_RGB( 0, 0, 0 ), CV_RGB( 255, 0, 0 ), 1, hopes_image );
            }
            
            /*for (int counter = 0; counter < hopes_graph.size(); ++counter)
            {
                Draw_Graph( hopes_graph[counter], scale, shift, 2, -1, 2, black, hopes_image ); // Drawing the output graph.
            }*/
            
            imwrite( BSD_directory + image_name + "/" + image_name + "_Hopes.png", hopes_image ); // Writing the image to a png file.
            
            cout << "Completed hopes algorithm on " << image_name << "." << endl << endl;
        }
    }
    
    if (BSD)
    {
        clock_t start_time = clock(); // Start stopwatch.
        
        int test_directory_size = 0, train_directory_size = 0, val_directory_size = 0;
        string test_directory = BSD_directory + "BSR/BSDS500/data/images/test/";
        string train_directory = BSD_directory + "BSR/BSDS500/data/images/train/";
        string val_directory = BSD_directory + "BSR/BSDS500/data/images/val/";
        
        for (auto & p : boost::filesystem::directory_iterator( test_directory ))
        {
            ++test_directory_size;
        }
        
        for (auto & p : boost::filesystem::directory_iterator( train_directory ))
        {
            ++train_directory_size;
        }
        
        for (auto & p : boost::filesystem::directory_iterator( val_directory ))
        {
            ++val_directory_size;
        }
        
        int directory_size = test_directory_size + train_directory_size + val_directory_size;
        int iterations = directory_size, skip = 0;
        double mapper_rms_error = 0, aR_rms_error = 0, hopes_rms_error = 0, mapper_max_error = 0, aR_max_error = 0, hopes_max_error = 0, mapper_time = 0, aR_time = 0, hopes_time = 0;
        string image_file;
        
        for (int counter_1 = 0; counter_1 < iterations; ++counter_1) // Looping over images.
        {
            if (!BSD_File( counter_1, test_directory, test_directory_size, train_directory, train_directory_size, val_directory, val_directory_size, image_file )) // Finding the file name of the image.
            {
                ++skip;
                continue;
            }
            
            Mat input_image;
             
            input_image = imread( image_file ); // Reading the image.
            
            vector<P2> cloud_p;
            vector<vector<P2>> clouds_p;
            vector<vector<Data_Pt>> clouds_d;
             
            Read_Cloud_From_Image( input_image, cloud_p, clouds_p, clouds_d ); // Extracting the cloud from the image.
            
            if (mapper_on_image) // Runs the image through the Mapper algorithm.
            {
                clock_t starttime = clock();
                
                vector<Graph> mapper_graph( clouds_p.size() );
                
                for (int counter = 0; counter < clouds_p.size(); ++counter) // Looping over clouds.
                {
                    Mapper_Parameters parameters( 15, 0.5, "Distance", 0.1, 3, 0 );
                    
                    Mapper( clouds_d[counter], parameters, mapper_graph[counter] ); // Generating the mapper graph.
                }
                
                Graph mapper;
                
                Combine_Comps( mapper_graph, mapper ); // Combining the components into a single graph.
                
                clock_t endtime = clock();
                
                mapper_time += (endtime - starttime) * 1000 / (double)(CLOCKS_PER_SEC);
                
                pair<double, double> results = Geometric_Approximation_Error( mapper, cloud_p ); // Calculating the RMS error of the output.
                
                mapper_max_error += results.first;
                mapper_rms_error += results.second;
            }
            
            if (alphaReeb_on_image) // Runs the image through the alpha-Reeb algorithm.
            {
                clock_t starttime = clock();
                
                vector<Graph> alphaReeb_graph( clouds_p.size() );
                
                for (int counter = 0; counter < clouds_p.size(); ++counter) // Looping over clouds.
                {
                    double epsilon;
                    
                    Find_Epsilon( clouds_p[counter], epsilon ); // Epsilon is used to create a nbhd graph of the cloud, and is equal to twice the max birth of cycles above the widest gap in the PD.
                    
                    Graph nbhd_graph;
                    
                    Cloud_To_Nbhd_Graph( clouds_d[counter], epsilon, nbhd_graph ); // Generating the neighbourhood graph of the cloud.
                    
                    AlphaReeb_Parameters parameters( 4, 0 );
                    
                    AlphaReeb_Algorithm( nbhd_graph, parameters, alphaReeb_graph[counter] ); // Alpha-Reeb algorithm.
                }
                
                Graph alphaReeb;
                
                Combine_Comps( alphaReeb_graph, alphaReeb ); // Combining the components into a single graph.
                
                clock_t endtime = clock();
                
                aR_time += (endtime - starttime) * 1000 / (double)(CLOCKS_PER_SEC);
                
                pair<double, double> results = Geometric_Approximation_Error( alphaReeb, cloud_p ); // Calculating the RMS error of the output.
                
                aR_max_error += results.first;
                aR_rms_error += results.second;
            }
            
            if (hopes_on_image) // Runs the image through the HoPeS algorithm.
            {
                clock_t starttime = clock();
                
                vector<Graph> hopes_graph( clouds_p.size() );
                
                for (int counter = 0; counter < clouds_p.size(); ++counter) // Looping over clouds.
                {
                    bool small_cloud = false;
                    double max_birth = 0, min_death = 1e10;
                    Graph_H g;
                    
                    if (hopes_simp_type_2 == 0) small_cloud = true;
                    
                    Hopes( clouds_p[counter], g, max_birth, min_death, small_cloud ); // Generating the Hopes graph.
                    
                    Simplify_Graph( g, hopes_simp_type_2, min_death, mcsf, hopes_graph[counter] ); // Simplifying the output.
                }
                
                Graph hopes;
                
                Combine_Comps( hopes_graph, hopes ); // Combining the components into a single graph.
                
                clock_t endtime = clock();
                
                hopes_time += (endtime - starttime) * 1000 / (double)(CLOCKS_PER_SEC);
                
                pair<double, double> results = Geometric_Approximation_Error( hopes, cloud_p ); // Calculating the RMS error of the output.
                
                hopes_max_error += results.first;
                hopes_rms_error += results.second;
            }
            
            cout << "Completed iteration " << counter_1 + 1 - skip << "." << endl << endl;
        }
        
        Write_Results( BSD_directory, mapper_rms_error, aR_rms_error, hopes_rms_error, mapper_max_error, aR_max_error, hopes_max_error, mapper_time, aR_time, hopes_time, iterations, skip );
        
        clock_t end_time = clock(); // End stopwatch.
        
        cout << "Duration: " << (end_time - start_time) / (double)CLOCKS_PER_SEC << "s." << endl << endl;
    }
    
    return 0;
}
