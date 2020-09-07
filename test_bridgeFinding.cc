
#include <iostream>

#include "BridgeFinding.h"
#include "Graph.h"


GraphLW< float > test_graph(){
    GraphLW< float > ret;

    ret.addNode( 0, { Edge< float >( 0, 1, 1. ), Edge< float >( 0, 2, 1. ) } );
    ret.addNode( 1, { Edge< float >( 1, 0, 1. ), Edge< float >( 1, 2, 1. ) } );
    ret.addNode( 2, { Edge< float >( 2, 0, 1. ), Edge< float >( 2, 1, 1. ), Edge< float >( 2, 3, 1. ), Edge< float >( 2, 5, 1. ) } );
    ret.addNode( 3, { Edge< float >( 3, 2, 1. ), Edge< float >( 3, 4, 1. ) } );
    ret.addNode( 4, { Edge< float >( 4, 3, 1. ) } );
    ret.addNode( 5, { Edge< float >( 5, 2, 1. ), Edge< float >( 5, 6, 1. ), Edge< float >( 5, 8, 1. ) } );
    ret.addNode( 6, { Edge< float >( 6, 5, 1. ), Edge< float >( 6, 7, 1. ) } );
    ret.addNode( 7, { Edge< float >( 7, 6, 1. ), Edge< float >( 7, 8, 1. ) } );
    ret.addNode( 8, { Edge< float >( 8, 5, 1. ), Edge< float >( 8, 7, 1. ) } );

    return ret;
}


int main(){

    auto graph = test_graph();
    auto bridges = findBridges( graph );
    for( auto& edge : bridges ){
        std::cout << edge << std::endl;
    }

    auto aps = findArticulationPoints( graph );
    for( auto& ap : aps ){
        std::cout << "articulation point at " << ap << std::endl;
    }
    return 0;
}
