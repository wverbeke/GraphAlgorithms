#ifndef Edge_H
#define Edge_H

#include <memory>
#include <exception>


template < typename T > class Edge{

    public:
        Edge( int f, int t, int c ): _from( f ), _to( t ), _capacity( c ){}
        
        void setResidual( Edge< T >* r ){ _residual = r; }

        int from() const{ return _from; }

        int to() const{ return _to; }

        T capacity() const{ return _capacity; }

        T remainingCapacity() const{ return ( _capacity - _flow ); }

        bool isResidual() const{ return _capacity <= 0; }

        void addFlow( T flow ){ 
            _flow += flow; 
            residual()->_flow -= flow;
        }

        Edge< T >* residual(){
            return _residual;
        };

    private:
        int _from;
        int _to;
        T _capacity;
        T _flow = 0;
        Edge< T >* _residual = nullptr;
};




#endif
