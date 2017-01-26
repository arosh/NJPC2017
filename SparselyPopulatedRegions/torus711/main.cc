// Problem : SparselyPopulatedRegions
// Author : torus711
// Expected : AC (sometimes RE due to stackoverflow)
// Complexity : O( N )

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

constexpr int INF = LIM<>::max() / 2;

using Edge = tuple< int, int, int >;
// ( to, cost, positive direction? )

int N, D;

VVT< Edge > G;

VI distances, costs;
void dfs1( const int u = 0, const int prev = -1 )
{
	if ( SZ( G[u] ) == 1 && get< 0 >( G[u][0] ) == prev )
	{
		distances[u] = costs[u] = 0;
		return;
	}

	FOR( e, G[u] )
	{
		const int v = get< 0 >( e );
		const int c = get< 1 >( e );
		const bool dir = get< 2 >( e );

		if ( v == prev )
		{
			continue;
		}

		dfs1( v, u );
	
		chmax( distances[u], distances[v] + c );
		costs[u] += costs[v] + dir;
	}

	return;
}

unsigned res = -1;

void dfs2( const int u, const int prev, const int dist, const int cost )
{
	if ( max( dist, distances[u] ) <= D )
	{
		chmin< unsigned >( res, cost );
	}

	if ( SZ( G[u] ) == 1 && get< 0 >( G[u][0] ) == prev )
	{
		return;
	}

	VPII dists;
	FOR( e, G[u] )
	{
		const int v = get< 0 >( e );
		const int c = get< 1 >( e );
		const bool dir = get< 2 >( e );

		if ( v == prev )
		{
			continue;
		}

		dists.EB( distances[v] + c, v );
	}
	sort( ALL( dists ), greater< PII >() );

	FOR( e, G[u] )
	{
		const int v = get< 0 >( e );
		const int c = get< 1 >( e );
		const bool dir = get< 2 >( e );

		if ( v == prev )
		{
			continue;
		}

		const int heaviest = v == dists[0].snd;
		const int nd = SZ( dists ) == 1
			? dist + c
			: max( dist + c, dists[ heaviest ].fst + c );
		dfs2( v, u, nd, cost + ( dir ? -1 : 1 ) );
	}

	return;
}

int main()
{
	cin.tie( 0 );
	ios::sync_with_stdio( false );

	scanf( "%d%d", &N, &D );

	G.resize( N );
	REP( i, N - 1 )
	{
		int u, v, c;
		scanf( "%d%d%d", &u, &v, &c );
		--u, --v;

		G[u].EB( v, c, 1 );
		G[v].EB( u, c, 0 );
	}

	distances.resize( N ), costs.resize( N );
	dfs1();
	dfs2( 0, -1, 0, costs[0] );

	printf( "%d\n", res );
	fflush( stdout );

	return 0;
}
