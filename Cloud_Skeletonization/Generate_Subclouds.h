#pragma once

#include "Data_Pt.h"

// Intervals function and Generate_Subclouds function for the alpha-Reeb algorithm.

void Intervals ( double alpha, double max, vector<pair<double, double>>& intervals )
{
	double interval_start = 0, interval_end;

	for (int counter = 0; interval_start < max; ++counter)
	{
		interval_start = 0.5 * counter * alpha;
		interval_end = (0.5 * counter + 1) * alpha;
		intervals.push_back( pair<double, double>( interval_start, interval_end ) );
	}
}

void Generate_Subclouds ( vector<Data_Pt>const& cloud, multimap<double, int>& filter_multimap, double alpha, vector<vector<Data_Pt>>& subcloud )
{
	vector<pair<double, double>> intervals;

	auto it = filter_multimap.rbegin();
	double max_dist_from_root = it->first;

	Intervals( alpha, max_dist_from_root, intervals ); // Finding intervals.
    
    size_t num_intervals = intervals.size();

	multimap<double, int>::iterator it_start, it_end;
	vector<pair<multimap<double, int>::iterator, multimap<double, int>::iterator>> pointers;

	for (int counter = 0; counter < num_intervals; ++counter)
	{
		it_start = filter_multimap.lower_bound( intervals[counter].first );
		it_end = filter_multimap.upper_bound( intervals[counter].second );
		pointers.push_back( make_pair( it_start, it_end ) );
	}
    
    subcloud.resize( num_intervals );

	for (int counter = 0; counter < num_intervals; ++counter)
	{
		for (auto it = pointers[counter].first; it != pointers[counter].second; ++it)
		{
			subcloud[counter].push_back( cloud[it->second] ); // Assigning points to subclouds.
		}
	}
}

// Intervals function and Generate_Subclouds function for the Mapper algorithm.

void Intervals ( double min, double max, int num_intervals, double overlap_ratio, vector<pair<double, double>>& intervals )
{
    double range = max - min;
    
    double length_interval = range / (double)(1 + (num_intervals - 1) * (1 - overlap_ratio));
    
    double interval_start, interval_end;
    
    for (int counter = 0; counter < num_intervals; ++counter)
    {
        interval_start = min + counter * length_interval * (1 - overlap_ratio);
        interval_end = interval_start + length_interval;
        intervals.push_back( make_pair( interval_start, interval_end ) );
    }
}

void Generate_Subclouds ( vector<Data_Pt>const& cloud, multimap<double, int>& filter_multimap, int num_intervals, double overlap_ratio, vector<vector<Data_Pt>>& subcloud )
{
    vector<pair<double, double>> intervals;
    
    auto it_1 = filter_multimap.begin();
    double min = it_1->first;
    auto it_2 = filter_multimap.rbegin();
    double max = it_2->first;
    
    Intervals( min, max, num_intervals, overlap_ratio, intervals ); // Finding intervals.
    
    multimap<double, int>::iterator it_start, it_end;
    vector<pair<multimap<double, int>::iterator, multimap<double, int>::iterator>> pointers;
    
    for (int counter = 0; counter < num_intervals; ++counter)
    {
        it_start = filter_multimap.lower_bound( intervals[counter].first );
        it_end = filter_multimap.upper_bound( intervals[counter].second );
        pointers.push_back( make_pair( it_start, it_end ) );
    }
    
    subcloud.resize( num_intervals );
    
    for (int counter = 0; counter < num_intervals; ++counter)
    {
        for (auto it = pointers[counter].first; it != pointers[counter].second; ++it)
        {
            subcloud[counter].push_back( cloud[it->second] ); // Assigning points to subclouds.
        }
    }
}
