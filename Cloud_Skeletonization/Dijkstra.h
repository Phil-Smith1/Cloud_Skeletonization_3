#pragma once

#include <boost/graph/dijkstra_shortest_paths.hpp>

#include "Graph.h"

void Dijkstra ( Graph const& g, multimap<double, int>& filter_multimap )
{
	vector<Graph::vertex_descriptor> parents(boost::num_vertices( g ));
	vector<double> distances(boost::num_vertices( g ));
	pair<vertex_iter, vertex_iter> VertexPair = boost::vertices( g );

	boost::dijkstra_shortest_paths( g, *VertexPair.first,
                                   boost::weight_map( boost::get( boost::edge_weight, g ) )
		.distance_map( boost::make_iterator_property_map( distances.begin(), boost::get( boost::vertex_index, g ) ) )
		.predecessor_map( boost::make_iterator_property_map( parents.begin(), boost::get( boost::vertex_index, g ) ) ) );

	size_t num_vertices = boost::num_vertices( g );

	for (int counter = 0; counter < num_vertices; ++counter)
	{
		filter_multimap.insert( pair<double, int>( distances[counter], counter ) );
	}
}
