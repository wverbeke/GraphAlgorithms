#ifndef Graph_H
#define Graph_H

#include <map>
#include <vector>

#include "Edge.h"


template < typename T > class Graph{


    public:
        using collection_type = typename std::map< int, std::vector< std::shared_ptr< Edge< T > > > >;
        using size_type = typename collection_type::size_type;
        using iterator = typename collection_type::iterator;
        using const_iterator = typename collection_type::const_iterator;

        Graph() = default;
        void addEdge( int from, int to, T capacity ){

            //add the real edge
            _adjecency_lists[ from ].push_back( std::make_shared< Edge< T > >( from, to, capacity ) );

            //add the residual
            _adjecency_lists[ to ].push_back( std::make_shared< Edge< T > >( to, from, 0 ) );

            //set eachothers residuals
            auto real_ptr = _adjecency_lists[ from ].back().get();
            auto res_ptr = _adjecency_lists[ to ].back().get();
            real_ptr->setResidual( res_ptr );
            res_ptr->setResidual( real_ptr );
        }

        std::vector< std::shared_ptr< Edge< T > > >& adList( int node ){ return _adjecency_lists.at( node ); }
        size_type numNodes() const{ return _adjecency_lists.size(); }

        iterator begin(){ return _adjecency_lists.begin(); }
        const_iterator begin() const{ return _adjecency_lists.cbegin(); }
        const_iterator cbegin() const{ return _adjecency_lists.cbegin(); }

        iterator end(){ return _adjecency_lists.end(); }
        const_iterator end() const{ return _adjecency_lists.cend(); }
        const_iterator cend() const{ return _adjecency_lists.cend(); }


    private:
        collection_type _adjecency_lists;
};


#endif
