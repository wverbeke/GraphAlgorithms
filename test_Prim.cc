

#include "Graph.h"
#include "Prim.h"

GraphLW< float > test_graph(){

    GraphLW< float > ret;

    ret.addNode( 0, { Edge< float >( 0, 1, 10 ), Edge< float >( 0, 2, 1 ), Edge< float >( 0, 3, 4 ) } );
    ret.addNode( 1, { Edge< float >( 1, 0, 10 ), Edge< float >( 1, 2, 3 ), Edge< float >( 1, 4, 0 ) } );
    ret.addNode( 2, { Edge< float >( 2, 0, 1 ), Edge< float >( 2, 1, 3 ), Edge< float >( 2, 3, 2 ), Edge< float >( 2, 5, 8 ) } );
    ret.addNode( 3, { Edge< float >( 3, 0, 4 ), Edge< float >( 3, 2, 2 ), Edge< float >( 3, 5, 2 ), Edge< float >( 3, 6, 7 ) } );
    ret.addNode( 4, { Edge< float >( 4, 1, 0 ), Edge< float >( 4, 5, 1 ), Edge< float >( 4, 7, 8 ) } );
    ret.addNode( 5, { Edge< float >( 5, 2, 8 ), Edge< float >( 5, 3, 2 ), Edge< float >( 5, 4, 1 ), Edge< float >( 5, 6, 6 ), Edge< float >( 5, 7, 9 ) } );
    ret.addNode( 6, { Edge< float >( 6, 3, 7 ), Edge< float >( 6, 5, 6 ), Edge< float >( 6, 7, 12 ) } );
    ret.addNode( 7, { Edge< float >( 7, 4, 8 ), Edge< float >( 7, 5, 9 ), Edge< float >( 7, 6, 12 ) } );

    return ret;
}


int main(){

    auto graph = test_graph();

    auto mst_cost = primMinimumSpanningTree( graph );

    std::cout << "minimum spamming tree (cost = " << mst_cost.second << "):" << std::endl;
    for( const auto& edge : mst_cost.first ){
        std::cout << edge << std::endl;
    }

    return 0;
}
