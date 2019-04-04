#pragma once

#include <opencv2/highgui/highgui.hpp>

#include <boost/graph/adjacency_list.hpp>

using namespace std;
using namespace cv;

struct VertexProperty
{
    int index;
    Point2d pt;
    int interval;
};

typedef boost::property<boost::edge_weight_t, double> EdgeProperty;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, VertexProperty, EdgeProperty> Graph;
typedef boost::graph_traits<Graph>::vertex_iterator vertex_iter;
typedef boost::graph_traits<Graph>::edge_iterator edge_iter;
typedef std::pair<edge_iter, edge_iter> EdgePair;
typedef boost::property_map<Graph, boost::edge_weight_t>::type Weight;
