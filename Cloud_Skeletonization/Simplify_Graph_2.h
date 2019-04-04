#pragma once

#include "Graph.h"

struct Fundamental_Error_Quadric
{
    double aa, ab, ac, bb, bc, cc;
};

void Simplify_Graph_2 ( Graph& g )
{
    vector<Fundamental_Error_Quadric> fundamental_error_quadrics;
    vector<pair<int, int>> valid_pairs;
    vector<vector<int>> incident_edges( boost::num_vertices( g ) );
    
    vector<Fundamental_Error_Quadric> Q;
    
    for (auto ei = boost::edges( g ).first; ei != boost::edges( g ).second; ++ei)
    {
        int src = (int)boost::source( *ei, g );
        int trg = (int)boost::target( *ei, g );
        
        valid_pairs.push_back( pair<int, int>( src, trg ) );
        
        incident_edges[src].push_back( (int)fundamental_error_quadrics.size() );
        
        Point2d source = g[boost::source( *ei, g )].pt;
        Point2d target = g[boost::target( *ei, g )].pt;
        
        double gradient = (target.y - source.y) / (double)(target.x - source.x);
        
        double f = 1 + gradient * gradient;
        
        double a = -gradient / (double)sqrt( f ), b = 1 / (double)sqrt( f ), c = -(a * source.x + b * source.y);
        
        Fundamental_Error_Quadric q;
        
        q.aa = a * a;
        q.ab = a * b;
        q.ac = a * c;
        q.bb = b * b;
        q.bc = b * c;
        q.cc = c * c;
        
        fundamental_error_quadrics.push_back( q );
    }
    
    for (auto it = incident_edges.begin(); it != incident_edges.end(); ++it)
    {
        Fundamental_Error_Quadric f;
        f.aa = 0;
        f.ab = 0;
        f.ac = 0;
        f.bb = 0;
        f.bc = 0;
        f.cc = 0;
        
        for (auto iter = it->begin(); iter != it->end(); ++it)
        {
            f.aa += fundamental_error_quadrics[*iter].aa;
            f.ab += fundamental_error_quadrics[*iter].ab;
            f.ac += fundamental_error_quadrics[*iter].ac;
            f.bb += fundamental_error_quadrics[*iter].bb;
            f.bc += fundamental_error_quadrics[*iter].bc;
            f.cc += fundamental_error_quadrics[*iter].cc;
        }
        
        Q.push_back( f );
    }
    
    int src = valid_pairs[0].first;
    int trg = valid_pairs[0].second;
    
    Fundamental_Error_Quadric new_Q;
    new_Q.aa = Q[src].aa + Q[trg].aa;
    new_Q.ab = Q[src].ab + Q[trg].ab;
    new_Q.ac = Q[src].ac + Q[trg].ac;
    new_Q.bb = Q[src].bb + Q[trg].bb;
    new_Q.bc = Q[src].bc + Q[trg].bc;
    new_Q.cc = Q[src].cc + Q[trg].cc;
    
    /*Graph g1;
    
    boost::add_vertex( g1 );
    boost::add_vertex( g1 );
    boost::add_vertex( g1 );
    
    pair<Graph::edge_descriptor, bool> e = boost::add_edge( 1, 2, g1 );
    
    cout << boost::num_vertices( g1 ) << endl;
    cout << boost::source( e.first, g1 ) << endl;
    cout << boost::target( e.first, g1 ) << endl;
    
    boost::remove_vertex( 0, g1 );
    
    cout << boost::num_vertices( g1 ) << endl;
    
    for (auto ei = boost::edges(g1).first; ei != boost::edges(g1).second; ++ei)
    {
        cout << boost::source( *ei, g1 ) << endl;
        cout << boost::target( *ei, g1 ) << endl;
    }*/
}
