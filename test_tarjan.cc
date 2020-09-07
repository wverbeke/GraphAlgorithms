
#include "Graph.h"
#include "Tarjan.h"


GraphLW< int > test_graph(){
    GraphLW< int > ret;

    ret.addNode( 0, { {1,1} } );
    ret.addNode( 1, { {2,1} } );
    ret.addNode( 2, { {0,1} } );
    
    ret.addNode( 3, { {4,1}, {7,1} } );
    ret.addNode( 4, { {5,1} } );
    ret.addNode( 5, { {0,1}, {6,1} } );
    ret.addNode( 6, { {0,1}, {4,1}, {2,1} } );
    ret.addNode( 7, { {3,1}, {5,1} } );

    return ret;
}

int main(){

    auto graph = test_graph();
    auto connectedComponents = tarjan( graph );

    for( const auto& entry : connectedComponents ){
        std::cout << "Nodes in component " << entry.first << " : ";
        for( const auto& node : entry.second ){
            std::cout << node << ", ";
        }
        std::cout << std::endl;
    }
    return 0;
}
