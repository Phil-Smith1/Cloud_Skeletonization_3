#include "Filtration.h"

bool Filtration::DecreasingLengths ( Edge const& e1, Edge const& e2 )
{
    return e2.length < e1.length;
}

int Filtration::FindRoot ( int node, vector<FH>const& faces )
{
    int next = faces[node]->info().uplink;
    if (next == node) return node;
    return FindRoot( next, faces );
}

bool Filtration::is_acute ( K::Triangle_2 const& Triangle, double& radius )
{
    double epsilon = 1.e-8;
    
    Point2d p0 = Point2d( Triangle.vertex(0).x(), Triangle.vertex(0).y() );
    Point2d p1 = Point2d( Triangle.vertex(1).x(), Triangle.vertex(1).y() );
    Point2d p2 = Point2d( Triangle.vertex(2).x(), Triangle.vertex(2).y() );
    
    double n1 = norm( p0 - p1 );
    double n2 = norm( p0 - p2 );
    
    Point2d p3 = (p0 - p1) / (double)n1;
    Point2d p4 = (p0 - p2) / (double)n2;
    
    if (p3.x < p4.x + epsilon && p3.x > p4.x - epsilon)
    {
        if (p3.y < p4.y + epsilon && p3.y > p4.y - epsilon)
        {
            return false;
        }
    }
    
    p4 = -1 * p4;
    
    if (p3.x < p4.x + epsilon && p3.x > p4.x - epsilon)
    {
        if (p3.y < p4.y + epsilon && p3.y > p4.y - epsilon)
        {
            return false;
        }
    }
    
    P2 p = circumcenter( Triangle.vertex( 0 ), Triangle.vertex( 1 ), Triangle.vertex( 2 ) );
    radius = sqrt( squared_distance( p, Triangle.vertex(0) ) );
    
    if ( Triangle.bounded_side( p ) == CGAL::ON_BOUNDED_SIDE ) return true;
    
    else return false;
}

// Edges and faces are defined in the constructor below.

Filtration::Filtration ( vector<P2>const& cloud )
{
    // Build a Delaunay triangulation.
    
    delaunay.clear();
    delaunay.insert( cloud.begin(), cloud.end() );
    
    if (delaunay.number_of_faces() != 0)
    {
        // Update info at vertices and faces: parent = itself, birth = circumradius for acute triangles.
        
        int ind = 0;
        
        for (VI iV = delaunay.vertices_begin(); iV != delaunay.vertices_end(); ++iV, ++ind) iV->info() = ind;
        
        faces.resize( delaunay.number_of_faces() + 1 );
        double radius = 0, death_max = 0;
        ind = 0;
        
        for (FFI iF = delaunay.finite_faces_begin(); iF != delaunay.finite_faces_end(); ++iF)
        {
            ++ind;
            faces[ind] = iF;
            faces[ind]->info().index = ind; // Set index.
            faces[ind]->info().uplink = ind; // Parent = itself.
            faces[ind]->info().live.resize( 1 );
            faces[ind]->info().live[0] = ind; // The only live triangle is the current.
            faces[ind]->info().birth = 0;
            
            K::Triangle_2 Triangle( iF->vertex(0)->point(), iF->vertex(1)->point(), iF->vertex(2)->point() );
            
            if ( !is_acute( Triangle, radius ) ) continue; // Non-acute triangle.
            
            faces[ind]->info().birth = radius;
            
            if (radius > death_max) death_max = radius;
        }
        
        faces[0] = delaunay.infinite_face(); // Default handle isn't used for external region.
        faces[0]->info().birth = death_max + 1e-2; // External region is born at alpha = death_max.
        faces[0]->info().index = 0;
        faces[0]->info().uplink = 0;
        faces[0]->info().live.resize( 1 );
        faces[0]->info().live[0] = 0;
        auto iF = faces[0];
        
        // Build vector DelEdges.
        
        ind = 0;
        
        for (FEI iE = delaunay.finite_edges_begin(); iE != delaunay.finite_edges_end(); ++iE, ++ind)
        {
            edges.push_back( Edge( *iE, ind ) );
        }
    }
}

void Filtration::Persistence1d ()
{
    // Cycle over edges to find all critical values.
    
    sort( edges.begin(), edges.end(), DecreasingLengths );
    
    double alpha = 0;
    int ind_edge = 0, Links = 0, nCases1 = 0, nCases2 = 0, nCases3 = 0, nCases4 = 0;
    
    for (; ind_edge < edges.size(); ++ind_edge)
    {
        Edge* CurEdge = &edges[ind_edge];
        alpha = 0.5 * CurEdge->length;
        int node_u = CurEdge->face1;
        int node_v = CurEdge->face2;
        int root_u = FindRoot( node_u, faces );
        int root_v = FindRoot( node_v, faces );
        
        if (root_u == root_v) // Case 1.
        {
            ++nCases1;
            negative_edges.push_back( ind_edge );
            continue;
        }
        
        Node_Data* Node_u = &faces[node_u]->info();
        Node_Data* Node_v = &faces[node_v]->info();
        Node_u->uplink = root_u; // Shorten path to root.
        Node_v->uplink = root_v; // Shorten path to root.
        Node_Data* Root_u = &faces[root_u]->info();
        Node_Data* Root_v = &faces[root_v]->info();
        double alpha_u = Root_u->birth; // faces[node_u]->info().birth.
        double alpha_v = Root_v->birth;
        
        if (alpha_u == 0 && alpha_v > 0) // Case 2: node u joins the region of node v.
        {
            ++nCases2;
            
            Node_u->uplink = root_v; // root_v becomes parent of root_u.
            Node_u->birth = alpha_v;
            
            if (Root_v->height == 1) Root_v->height = 2; // Node_u added to the tree at root_v.
            
            int r = Node_v->bar; // Index of the region containing the triangle T_v.
            
            if (r >= 0) // The region is already dead.
            {
                Node_u->bar = r; // Node_u joins the dead region of node_v
                map[r].core.push_back( node_u );
            }
            
            else Root_v->live.push_back( node_u ); // node_u becomes a live triangle at root_v.
            
            Node_u->live.clear();
        }
        
        else if (alpha_u > 0 && alpha_v == 0) // Symmetric case 2: node_v joins the region of node_u.
        {
            ++nCases2;
            
            Node_v->uplink = root_u;
            Node_v->birth = alpha_u;
            
            if (Root_u->height == 1) Root_u->height = 2; // Node_v added to the tree at Root_u.
            
            int r = Node_u->bar; // Index the region containing the triangle T_u.
            
            if (r >= 0) // The region is already dead.
            {
                Node_v->bar = r; // Node_v joins the dead region of Node_u.
                map[r].core.push_back( node_v );
            }
            
            else Root_u->live.push_back( node_v ); // node_v becomes a live triangle at root_u.
            
            Node_v->live.clear();
        }
        
        else if (alpha_u == 0 && alpha_v == 0) // Case 3: two right-angled triangles at node_u, node_v.
        {
            ++nCases3;
            
            Node_v->uplink = node_u; // root_u = node_u becomes parent of root_v = node_v.
            
            if (Node_u->height == 1) Node_u->height = 2; // Node_v is now attached to its parent Node_u.
            
            Node_u->birth = alpha;
            Node_v->birth = alpha;
            Node_u->live.push_back( node_v );
            Node_v->live.clear();
        }
        
        else if (alpha_u > 0 && alpha_v > 0) // Case 4: merge the regions of node_u, node_v.
        {
            ++nCases4;
            
            double death = min( alpha_u, alpha_v );
            int heir = -1, supr = -1, ind = (int)map.size(); // Index of the newly added region.
            
            persistence.push_back( Life( ind, alpha, death, ind_edge ) ); // Younger class dies and is recorded.
            
            // Create a new region (in Map) corresponding to a dot in the persistence diagram.
            
            if (Root_u->birth <= Root_v->birth) // u is younger than v.
            {
                // Set bar index for all live triangles at root_u.
                
                for (int i = 0; i < Root_u->live.size(); ++i) faces[Root_u->live[i]]->info().bar = ind;
                
                if (Node_v->bar < 0) heir = node_v; // node_v is still alive and will be the heir.
                
                else supr = Node_v->bar; // bar index of the already dead region containing T_v.
                
                map.push_back( Region( ind, alpha, death, Root_u->live, heir, supr, ind_edge ) );
                
                if (Root_u->height > Root_v->height) // u is younger, but higher than v.
                {
                    Root_v->uplink = root_u;
                    Root_u->live = Root_v->live; // Triangles from Root_v->live are saved to the higher Root_u->live.
                    Root_u->birth = Root_v->birth; // The new root now has the earliest birth.
                }
                
                else // u is younger and lower than v.
                {
                    Root_u->uplink = root_v;
                    if (Root_u->height == Root_v->height) Root_v->height ++;
                }
            }
            
            else // v is younger (than u) and dies.
            {
                for (int i = 0; i < Root_v->live.size(); ++i) faces[Root_v->live[i]]->info().bar = ind;
                
                if (Node_u->bar < 0) heir = node_u; // root_u still alive and will be the heir.
                
                else supr = Node_u->bar; // bar index of the already dead region containing T_u.
                
                map.push_back( Region( ind, alpha, death, Root_v->live, heir, supr, ind_edge ) );
                
                if (Root_u->height >= Root_v->height) // v is younger and lower than v.
                {
                    Root_v->uplink = root_u;
                    if (Root_u->height == Root_v->height) Root_u->height ++;
                }
                
                else // v is younger, but higher than u.
                {
                    Root_u->uplink = root_v;
                    Root_v->live = Root_u->live;
                    Root_v->birth = Root_u->birth;
                }
            }
        }
        
        ++Links;
        
        if (Links >= delaunay.number_of_faces()) break;
    }
    
    for (int i = ind_edge + 1; i < edges.size(); ++i) negative_edges.push_back( i );
    
    if (negative_edges.size() + 1 != delaunay.number_of_vertices()) cout << "\nError with Negative Edges.\n";
    
    // Add the final unbounded region to Map.
    
    int root = FindRoot( 0, faces );
    Node_Data* N = &faces[root]->info();
    
    for (int i=0; i < N->live.size(); ++i) faces[N->live[i]]->info().bar = (int)map.size();
    
    map.push_back( Region( (int)map.size(), alpha, N->birth, N->live, -1, (int)map.size(), -1 ) ); // Last heir irrelevant.
    
    // Output intermediate results.
    
    int SumCores = 0;
    
    for (int j = 0; j < map.size() - 1; ++j) SumCores += map[j].core.size();
    
    int ExtCore = (int)map[ map.size()-1 ].core.size();
    
    if (SumCores + ExtCore != delaunay.number_of_faces() + 1) cout << "\nError with cores of initial regions.\n";
    
    for (size_t i = 0; i < persistence.size(); ++i) positive_edges.push_back( persistence[i].edge );
    
    /*negative_edges.clear();
    for (int ei = 0; ei < edges.size(); ++ei)
    {
        negative_edges.push_back( ei );
    }*/
}

Filtration::Filtration(){}
Filtration::~Filtration(){}
