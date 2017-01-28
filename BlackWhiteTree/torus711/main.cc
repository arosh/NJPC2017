// Problem : BlackWhiteTree
// Author : torus711
// Expected : AC
// Complexity : O( N + Q log N )

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

// Fenwick Tree ( Binary Indexed Tree )
template < typename T >
class FenwickTree 
{
private:
	const int N;
	std::vector< T > data;

public:
	FenwickTree( const int n ) : N( n ), data( N + 1, 0 ) {}

	T sum( int i ) const
	{
		++i;
		T res = 0;
		while ( 0 < i )
		{
			res += data[i];
			i -= i & -i;
		}
		return res;
	}

	T sum( const int l, const int r ) const
	{
		return l ? sum( r - 1 ) - sum( l - 1 ) : sum( r - 1 );
	}

	void add( int i, const T x )
	{
		++i;
		while ( i <= N )
		{
			data[i] += x;
			i += i & -i;
		}
		return;
	}

	void change( const int i, const T x )
	{
		add( i, x - ( sum( i ) - ( i ? sum( i - 1 ) : 0 ) ) );
		return;
	}

	int lower_bound( T v ) const
	{
		int x = 0;
		for ( int k = 1 << ( 31 - __builtin_clz( N ) ); k; k >>= 1 )
		{
			if ( x + k <= N && data[ x + k ] < v )
			{
				x += k;
				v -= data[x];
			}
		}
		return x;
	}
};
// FenwickTree( array size )
// int sum( 0-indexed pos )
// int sum( [ l, r )
// int add( pos, value )
// int change( pos, value )
// int lower_bound( value )

class LowestCommonAncestor
{
private:
	const int N;
	std::vector< VPII > G;

	bool constructed = false;
	std::vector<int> depth_, distances_;
	std::vector< std::vector<int> > parent_;

public:
	LowestCommonAncestor( const int n ) : N( n ), G( N ), depth_( N ), distances_( N ), parent_( N, std::vector<int>( 31, -1 ) )
	{
		return;
	}

	void connect( const int u, const int v, const int d = 1 )
	{
		G[u].EB( v, d );
		G[v].EB( u, d );
		constructed = false;

		return;
	}

	int depth( const int u ) const
	{
		return depth_[u];
	}

	int solve( int u, int v )
	{
		if ( !constructed )
		{
			dfs( 0, -1, 0, 0 );
			doubling();
			constructed = true;
		}

		if ( depth_[u] < depth_[v] )
		{
			swap( u, v );
		}

		{ // align depths
			int diff = depth_[u] - depth_[v];
			for ( int i = 30; 0 <= i; --i )
			{
				if ( diff & 1 << i )
				{
					u = parent_[u][i];
				}
			}
		}

		if ( u == v )
		{
			return u;
		}

		for ( int i = 30; 0 <= i; --i )
		{
			if ( parent_[u][i] != parent_[v][i] )
			{
				u = parent_[u][i];
				v = parent_[v][i];
			}
		}

		return parent_[u][0];
	}

	int distance( const int u, const int v )
	{
		const int w = solve( u, v );
		return distances_[u] + distances_[v] - 2 * distances_[w];
	}

private:
	void dfs( const int u, const int prev, const int d, const int dist )
	{
		depth_[u] = d;
		parent_[u][0] = prev;
		distances_[u] = dist;

		for ( const PII &e : G[u] )
		{
			const int v = e.fst;
			if ( v == prev )
			{
				continue;
			}

			dfs( v, u, d + 1, dist + e.snd );
		}

		return;
	}

	void doubling()
	{
		for ( int i = 0; i < 30; ++i )
		{
			for ( int u = 0; u < N; ++u )
			{
				if ( parent_[u][i] != -1 )
				{
					parent_[u][ i + 1 ] = parent_[ parent_[u][i] ][i];
				}
			}
		}
		return;
	}
};
// LowestCommonAncestor( N )
// connect( u, v [, dist = 1 ] )
// solve( u, v )
// depth( u )
// distance( u, v )

int N;
int P[ 1 << 17 ], C[ 1 << 17 ];

VVI G, occurences;
int K = 0;

void dfs( const int u = 0 )
{
	occurences[u].PB( K );
	K += 2;

	FOR( v, G[u] )
	{
		dfs( v );

		occurences[u].PB( K );
		K += 2;
	}

	return;
}

int main()
{
	cin.tie( 0 );
	ios::sync_with_stdio( false );

	scanf( "%d", &N );

	G.resize( N );
	LowestCommonAncestor lca( N );
	REP( i, 1, N )
	{
		scanf( "%d", P + i );
		--P[i];

		G[ P[i] ].PB( i );
		lca.connect( P[i], i );
	}
	REP( i, N )
	{
		scanf( "%d", C + i );
	}

	occurences.resize( N );
	dfs();

	FenwickTree< int > fenwick( K );
	REP( i, 1, N )
	{
		if ( C[i] == C[ P[i] ] )
		{
			fenwick.add( occurences[i][0] - 1, 1 );
			fenwick.add( occurences[i].back() + 1, -1 );
		}
	}

	int Q;
	scanf( "%d", &Q );

	REP( _, Q )
	{
		int type;
		scanf( "%d", &type );

		if ( type == 1 )
		{
			int u;
			scanf( "%d", &u );
			--u;

			if ( u )
			{
				const int val = fenwick.sum( occurences[u][0] - 1, occurences[u][0] ) ? -1 : 1;
				fenwick.add( occurences[u][0] - 1, val );
				fenwick.add( occurences[u].back() + 1, -val );
			}
		}
		else
		{
			int u, v;
			scanf( "%d%d", &u, &v );
			--u, --v;

			const int p = occurences[u][0];
			const int q = occurences[v][0];
			const int l = occurences[ lca.solve( u, v ) ][0];

			puts( fenwick.sum( 0, p ) + fenwick.sum( 0, q ) - 2 * fenwick.sum( 0, l ) ? "NO" : "YES" );
		}
	}

	fflush( stdout );

	return 0;
}
