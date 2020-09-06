
#include <iostream>
#include <limits>
#include "Graph.h"
#include "FloydWarshall.h"


GraphMW< double > test_graph(){

    GraphMW< double > ret( 7 );
    ret[0][1] = 2;
    ret[0][2] = 5;
    ret[0][6] = 10;
    ret[1][2] = 2;
    ret[1][4] = 11;
    ret[2][6] = 2;
    ret[6][5] = 11;
    ret[4][5] = 1;
    ret[5][4] = -2;
    return ret;
}



int main(){

    auto graph = test_graph();
    auto dist_next = floydWarshall( graph );

    auto dist = dist_next.first;
    auto next = dist_next.second;

    for( int i = 0; i < dist.size(); ++i ){
        for( int j = 0; j < dist.size(); ++j ){
            std::cout << "shortest path from node " << i << " to node " << j << " is " << dist[ i ][ j ] << std::endl;
        }
    }

    /*
    for( const auto& row : next ){
        for( const auto& column : row ){
            std::cout << column << "  ";
        }
        std::cout << std::endl;
    }
    */

    for( int i = 0; i < dist.size(); ++i ){
        for( int j = 0; j < dist.size(); ++j ){
            auto path = reconstructPath( i, j, next, dist );
            std::cout << "The shortest path from node " << i << " to node " << j;
            if( path.empty() ){
                std::cout << " DOES NOT EXIST (node " << i << " doesn't reach node " << j << ")" << std::endl;
            } else if( path[0] == -1 ){
                std::cout << " HAS AN infinite NUMBER OF SOLUTIONS! (negative cycle case)" << std::endl;
            } else {
                std::cout << " is: [";
                //for( const auto& entry : path ){
                for( auto it = path.cbegin(); it != path.cend(); ++it ){
                    std::cout << *it;
                    if( it < path.cend() - 1 ){
                        std::cout << " -> ";
                    } else {
                        std::cout << "]";
                    }
                }
                std::cout << std::endl;
            }
        }
    }

    return 0;
}
