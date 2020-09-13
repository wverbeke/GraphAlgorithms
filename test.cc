#include "Graph.h"
#include "DepthFirstSearch.h"
#include "BreadthFirstSearch.h"


GraphL testGraph(){

    GraphL ret;
    ret.addNode( 0, {1,9} );
    ret.addNode( 1, {0,8} );
    ret.addNode( 9, {0,8} );
    ret.addNode( 8, {1,7,9} );
    ret.addNode( 7, {3,6,8,10,11} );
    ret.addNode( 10, {7,11} );
    ret.addNode( 11, {7,10} );
    ret.addNode( 6, {5,7} );
    ret.addNode( 5, {3,6} );
    ret.addNode( 3, {4,2,5} );
    ret.addNode( 4, {3} );
    ret.addNode( 2, {3} );
    return ret;
}


GraphL disconnected(){

    GraphL ret;

    //component 1
    ret.addNode( 6, {7, 11} );
    ret.addNode( 7, {6, 11} );
    ret.addNode( 11, {6,7 } );

    //component 2
    ret.addNode( 12, {} );
    
    //component 3
    ret.addNode( 4, {8,0} );
    ret.addNode( 8, {0,4,14} );
    ret.addNode( 0, {4,8,13,14} );
    ret.addNode( 14, {0,8,13} );
    ret.addNode( 13, {0,14} );

    //component 4
    ret.addNode( 3, {9} );
    ret.addNode( 9, {3,15,2} );
    ret.addNode( 2, {9,15} );
    ret.addNode( 15, {2,9,10} );
    ret.addNode( 10, {15} );


    //component 5
    ret.addNode( 17, {5} );
    ret.addNode( 5, {17,1,16} );
    ret.addNode( 1, {5} );
    ret.addNode( 16, {5} );

    return ret;
}

template< typename T > void print( const T& container ){

    for( const auto& entry : container ){
        std::cout << entry << ", ";
    }
    std::cout << std::endl;
}


int main(){

    GraphL disc = disconnected();

    auto connected = connectedComponents( disc );
    for( const auto& entry : connected ){
        std::cout << "index " << entry.first << " : ";
        for( const auto& node : entry.second ){
            std::cout << node << ", ";
        }
        std::cout << std::endl;
    }

    GraphL test = testGraph();
    auto path = shortestPath( test, 7, 0);
    print( path );
    
}
