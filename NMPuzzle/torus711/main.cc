// Problem : NM Puzzle
// Author : torus711
// Expected : AC
// Complexity : O( NM^2 ) where N <= M (w.l.o.g)

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <stack>
#include <queue>
#include <deque>
#include <algorithm>
#include <functional>
#include <iterator>
#include <limits>
#include <numeric>
#include <utility>
#include <cmath>
#include <cassert>
#include <cstdio>

using namespace std;
using namespace placeholders;

using LL = long long;
using ULL = unsigned long long;
using VI = vector< int >;
using VVI = vector< vector< int > >;
using VS = vector< string >;
using SS = stringstream;
using PII = pair< int, int >;
using VPII = vector< pair< int, int > >;
template < typename T = int > using VT = vector< T >;
template < typename T = int > using VVT = vector< vector< T > >;
template < typename T = int > using LIM = numeric_limits< T >;

template < typename T > inline istream& operator>>( istream &s, vector< T > &v ){ for ( T &t : v ) { s >> t; } return s; }
template < typename T > inline ostream& operator<<( ostream &s, const vector< T > &v ){ for ( int i = 0; i < int( v.size() ); ++i ){ s << ( " " + !i ) << v[i]; } return s; }
template < typename T > inline T fromString( const string &s ) { T res; istringstream iss( s ); iss >> res; return res; }
template < typename T > inline string toString( const T &a ) { ostringstream oss; oss << a; return oss.str(); }

#define REP2( i, n ) REP3( i, 0, n )
#define REP3( i, m, n ) for ( int i = ( int )( m ); i < ( int )( n ); ++i )
#define GET_REP( a, b, c, F, ... ) F
#define REP( ... ) GET_REP( __VA_ARGS__, REP3, REP2 )( __VA_ARGS__ )
#define FOR( e, c ) for ( auto &&e : c )
#define ALL( c ) begin( c ), end( c )
#define AALL( a, t ) ( t* )a, ( t* )a + sizeof( a ) / sizeof( t )
#define DRANGE( c, p ) ( c ).begin(), ( c ).begin() + ( p ), ( c ).end()

#define SZ( v ) ( (int)( v ).size() )
#define EXIST( c, e ) ( ( c ).find( e ) != ( c ).end() )

template < typename T > inline bool chmin( T &a, const T &b ){ if ( b < a ) { a = b; return true; } return false; }
template < typename T > inline bool chmax( T &a, const T &b ){ if ( a < b ) { a = b; return true; } return false; }

#define PB push_back
#define EM emplace
#define EB emplace_back
#define BI back_inserter

#define MP make_pair
#define fst first
#define snd second

#define DUMP( x ) cerr << #x << " = " << ( x ) << endl

VI transpose( const VI &A, const int H, const int W )
{
	VI res;
	REP( j, W )
	{
		REP( i, H )
		{
			res.PB( A[ i * W + j ] );
		}
	}
	return move( res );
}

void print_matrix( const VI &A, const int H, const int W )
{
	REP( i, H )
	{
		cout << VI( begin( A ) + i * W, begin( A ) + ( i + 1 ) * W ) << endl;
	}
	return;
}

int main()
{
	cin.tie( 0 );
	ios::sync_with_stdio( false );

	int H, W, K;
	cin >> H >> W >> K;

	const int MAX_INVERSE = H * W * ( W - 1 ) / 2 + W * H * ( H - 1 ) / 2;

	VI flatten( H * W );
	iota( ALL( flatten ), 1 );

	const bool transposed = W < H;
	if ( transposed )
	{
		swap( H, W );
	}

	const bool increase = K * 2 <= MAX_INVERSE;
	if ( !increase )
	{
		reverse( ALL( flatten ) );
	}

	int inverse = increase ? 0 : MAX_INVERSE;

	if ( inverse == K )
	{
		if ( transposed )
		{
			flatten = transpose( flatten, H, W );
			swap( H, W );
		}
		print_matrix( flatten, H, W );
		return 0;
	}

	REP( i, H )
	{
		for ( int l = W - 1; 0 <= l; --l )
		{
			REP( j, l )
			{
				swap( flatten[ i * W + j ], flatten[ i * W + j + 1 ] );
				inverse += increase ? 1 : -1;
				if ( inverse == K )
				{
					if ( transposed )
					{
						flatten = transpose( flatten, H, W );
						swap( H, W );
					}
					print_matrix( flatten, H, W );
					return 0;
				}
			}
		}
	}

	return 0;
}
