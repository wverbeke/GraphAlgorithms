#include <iostream>

#include "Graph.h"
#include "BellmanFord.h"


GraphLW< double > test_graph(){
    GraphLW< double > ret;
    ret.addNode( 0, { {1,5} } );
    ret.addNode( 1, { {2,20}, {5,30}, {6,60} } );
    ret.addNode( 2, { {3,10}, {4,75} } );
    ret.addNode( 3, { {2,-15} } );
    ret.addNode( 4, { {9,100} } );
    ret.addNode( 5, { {6,5}, {8,50} } );
    ret.addNode( 6, { {7,-50} } );
    ret.addNode( 7, { {8,-10} } );
    ret.addNode( 8, {} );
    ret.addNode( 9, {} );

    return ret;

}


int main(){
    
    auto graph = test_graph();

    auto dist = bellmanFord( graph, 0 );

    for( const auto& entry : dist ){
        std::cout << entry << std::endl;
    }

    return 0;
}
