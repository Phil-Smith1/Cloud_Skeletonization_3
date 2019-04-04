#pragma once

#include "Graph.h"

void Root ( vector<pair<bool, int>>const& tree, int& ptr )
{
    while (!tree[ptr].first)
    {
        ptr = tree[ptr].second;
    }
}

void Generate_AlphaReeb_Graph ( Graph& input_graph, double alpha, Graph& alphaReeb_graph )
{
    size_t num_vertices = boost::num_vertices( input_graph );
    
    vector<pair<bool, int>> vertex_tree( 3 * num_vertices, pair<bool, int>( true, -1 ) );
    vector<vector<int>> dependencies( 3 * num_vertices );
    vector<pair<bool, int>> edge_tree( 2 * num_vertices, pair<bool, int>( true, -1 ) );
    
    for (auto ei = boost::edges( input_graph ).first; ei != boost::edges( input_graph ).second; ++ei)
    {
        int source, target;
        
        if (input_graph[boost::source( *ei, input_graph )].interval < input_graph[boost::target( *ei, input_graph )].interval)
        {
            source = input_graph[boost::source( *ei, input_graph )].index;
            target = input_graph[boost::target( *ei, input_graph )].index;
        }
        
        else
        {
            source = input_graph[boost::target( *ei, input_graph )].index;
            target = input_graph[boost::source( *ei, input_graph )].index;
        }
        
        int s = 2 * source + 1;
        int t = 2 * target;
        
        Root( edge_tree, s );
        Root( edge_tree, t );
        
        if (s != t)
        {
            edge_tree[t].first = false;
            edge_tree[t].second = s;
        }
        
        s = 3 * source + 1;
        t = 3 * target;
        
        Root( vertex_tree, s );
        Root( vertex_tree, t );
        
        if (s != t)
        {
            vertex_tree[t].first = false;
            vertex_tree[t].second = s;
            dependencies[s].push_back( t );
        }
        
        s = 3 * source + 2;
        t = 3 * target + 1;
        
        Root( vertex_tree, s );
        Root( vertex_tree, t );
        
        if (s != t)
        {
            vertex_tree[s].first = false;
            vertex_tree[s].second = t;
            dependencies[t].push_back( s );
        }
    }
    
    vector<Graph::vertex_descriptor> vd;
    vector<pair<Graph::edge_descriptor, bool>> e;
    
    for (int counter = 0; counter < 3 * num_vertices; ++counter)
    {
        if (vertex_tree[counter].first)
        {
            vertex_tree[counter].second = (int)vd.size();
            
            vd.push_back( boost::add_vertex( alphaReeb_graph ) );
            
            if (counter % 3 == 1)
            {
                alphaReeb_graph[vd.back()].pt = input_graph[(counter - 1) / 3].pt;
            }
            
            else if (counter % 3 == 0)
            {
                alphaReeb_graph[vd.back()].pt = input_graph[counter / 3].pt - Point2d( 0, alpha / (double)2 );
            }
            
            else
            {
                alphaReeb_graph[vd.back()].pt = input_graph[(counter - 2) / 3].pt + Point2d( 0, alpha / (double)2 );
            }
        }
    }
    
    for (int counter = 0; counter < 3 * num_vertices; ++counter)
    {
        vector<int> deps;
        
        for (auto it = dependencies[counter].begin(); it != dependencies[counter].end(); ++it)
        {
            if (*it % 3 == 1) deps.push_back( *it );
        }
        
        if (deps.size() != 0)
        {
            for (auto it = deps.begin(); it != deps.end(); ++it)
            {
                input_graph[(counter - 1) / 3].pt += input_graph[(*it - 1) / 3].pt;
            }
            
            input_graph[(counter - 1) / 3].pt = Point2d( input_graph[(counter - 1) / 3].pt.x / (double)(deps.size() + 1), input_graph[(counter - 1) / 3].pt.y / (double)(deps.size() + 1) );
        }
    }
    
    for (int counter = 0; counter < 3 * num_vertices; ++counter)
    {
        if (vertex_tree[counter].first)
        {
            if (counter % 3 == 1)
            {
                alphaReeb_graph[vertex_tree[counter].second].pt = input_graph[(counter - 1) / 3].pt;
            }
        }
    }
    
    for (int counter = 0; counter < 2 * num_vertices; ++counter)
    {
        if (edge_tree[counter].first)
        {
            int source, target;
            
            if (counter % 2 == 0)
            {
                source = counter * 1.5;
                target = counter * 1.5 + 1;
            }
            
            else
            {
                source = (counter - 1) * 1.5 + 1;
                target = (counter - 1) * 1.5 + 2;
            }
            
            Root( vertex_tree, source );
            Root( vertex_tree, target );
            
            source = vertex_tree[source].second;
            target = vertex_tree[target].second;
            
            e.push_back( boost::add_edge( source, target, alphaReeb_graph ) );
            Point2d src = alphaReeb_graph[boost::source( e.back().first, alphaReeb_graph )].pt;
            Point2d trg = alphaReeb_graph[boost::target( e.back().first, alphaReeb_graph )].pt;
            double length = norm( trg - src );
            boost::put( boost::edge_weight_t(), alphaReeb_graph, e.back().first, length );
        }
    }
    
    bool removed_edge = true;
    
    while (removed_edge)
    {
        removed_edge = false;
        
        for (auto ei = boost::edges( alphaReeb_graph ).first; ei != boost::edges( alphaReeb_graph ).second; ++ei)
        {
            for (auto oei = boost::out_edges( boost::source( *ei, alphaReeb_graph ), alphaReeb_graph ).first; oei != boost::out_edges( boost::source( *ei, alphaReeb_graph ), alphaReeb_graph ).second; ++oei)
            {
                if (boost::target( *oei, alphaReeb_graph ) == boost::target( *ei, alphaReeb_graph ) && *oei != *ei)
                {
                    int source = (int)boost::source( *ei, alphaReeb_graph ), target = (int)boost::target( *ei, alphaReeb_graph );
                    
                    boost::remove_edge( source, target, alphaReeb_graph );
                    
                    removed_edge = true;
                    
                    Point2d vect = alphaReeb_graph[target].pt - alphaReeb_graph[source].pt;
                    Point2d vect_perp = Point2d( -vect.y, vect.x );
                    Point2d intermediate_1 = alphaReeb_graph[source].pt + 0.5 * vect + 0.5 * vect_perp;
                    Point2d intermediate_2 = alphaReeb_graph[source].pt + 0.5 * vect - 0.5 * vect_perp;
                    
                    vd.push_back( boost::add_vertex( alphaReeb_graph ) );
                    alphaReeb_graph[vd.back()].pt = intermediate_1;
                    
                    e.push_back( boost::add_edge( source, vd.back(), alphaReeb_graph ) );
                    Point2d src = alphaReeb_graph[boost::source( e.back().first, alphaReeb_graph )].pt;
                    Point2d trg = alphaReeb_graph[boost::target( e.back().first, alphaReeb_graph )].pt;
                    double length = norm( trg - src );
                    boost::put( boost::edge_weight_t(), alphaReeb_graph, e.back().first, length );
                    
                    e.push_back( boost::add_edge( vd.back(), target, alphaReeb_graph ) );
                    src = alphaReeb_graph[boost::source( e.back().first, alphaReeb_graph )].pt;
                    trg = alphaReeb_graph[boost::target( e.back().first, alphaReeb_graph )].pt;
                    length = norm( trg - src );
                    boost::put( boost::edge_weight_t(), alphaReeb_graph, e.back().first, length );
                    
                    vd.push_back( boost::add_vertex( alphaReeb_graph ) );
                    alphaReeb_graph[vd.back()].pt = intermediate_2;
                    
                    e.push_back( boost::add_edge( source, vd.back(), alphaReeb_graph ) );
                    src = alphaReeb_graph[boost::source( e.back().first, alphaReeb_graph )].pt;
                    trg = alphaReeb_graph[boost::target( e.back().first, alphaReeb_graph )].pt;
                    length = norm( trg - src );
                    boost::put( boost::edge_weight_t(), alphaReeb_graph, e.back().first, length );
                    
                    e.push_back( boost::add_edge( vd.back(), target, alphaReeb_graph ) );
                    src = alphaReeb_graph[boost::source( e.back().first, alphaReeb_graph )].pt;
                    trg = alphaReeb_graph[boost::target( e.back().first, alphaReeb_graph )].pt;
                    length = norm( trg - src );
                    boost::put( boost::edge_weight_t(), alphaReeb_graph, e.back().first, length );
                    
                    break;
                }
            }
            
            if (removed_edge) break;
        }
    }
}
