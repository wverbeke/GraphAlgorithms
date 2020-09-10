
#include "Graph.h"
#include "EulerianPath.h"


GraphLW< int > test_graph(){

    GraphLW< int > ret;

    ret.addNode( 0, {} );
    ret.addNode( 1, { Edge< int >( 1, 2, 1 ), Edge< int >( 1, 3, 1 ) } );
    ret.addNode( 2, { Edge< int >( 2, 2, 1 ), Edge< int >( 2, 4, 1 ), Edge< int >( 2, 4, 1 ) } ); //self-edge and 2 edges to 4
    ret.addNode( 3, { Edge< int >( 3, 1, 1 ), Edge< int >( 3, 2, 1 ), Edge< int >( 3, 5, 1 ) } );
    ret.addNode( 4, { Edge< int >( 4, 3, 1 ), Edge< int >( 4, 6, 1 ) } );
    ret.addNode( 5, { Edge< int >( 5, 6, 1 ) } );
    ret.addNode( 6, { Edge< int >( 6, 3, 1 ) } );

    return ret;
}


int main(){

    auto graph = test_graph();
    
    auto ePath = eulerianPath( graph );

    for( auto& entry : ePath ){
        std::cout << entry << std::endl;
    }
}
