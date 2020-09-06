#include "Dijkstra.h"
#include "Graph.h"


GraphLW< int > test_graph(){
    GraphLW<int> ret;
    
    ret.addNode( 0, { {1,4}, {2,1} } );
    ret.addNode( 1, { {3,1} } );
    ret.addNode( 2, { {1,2}, {3,5} } );
    ret.addNode( 3, { {4,3} } );
    ret.addNode( 4, { } );

    return ret;

}


int main(){

    auto graph = test_graph();

    auto distances = dijkstraLazy( graph, 0 ).first;

    for( size_t i = 0; i < distances.size(); ++i ){
        std::cout << "distance to " << i << "  = " << distances[i] << std::endl;
    }

    auto path = shortestPath( graph, 0, 4 );
    for( const auto& entry : path ){
        std::cout << entry << "\t";
    }
    std::cout << std::endl;

    return 0;
}
