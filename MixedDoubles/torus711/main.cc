// Problem : MixedDoubles
// Author : torus711
// Expected : AC
// Complexity : O( N log W ) where W = width of coordinate

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

constexpr double INF = 1e9;
constexpr double EPS = 1e-9;

int N;
int T[ 1 << 17 ], X[ 1 << 17 ];

bool possible( const double V )
{
	int t = 0;
	double l = 0, r = 0;

	REP( i, N )
	{
		const double W = V * ( T[ i + 1 ] - T[i] );
		double nl = INF, nr = -INF;

		if ( X[i] - W - EPS <= X[ i + 1 ] && X[ i + 1 ] <= X[i] + W + EPS )
		{
			chmin( nl, l - W );
			chmax( nr, r + W );
		}
		if ( l - W - EPS <= X[ i + 1 ] && X[ i + 1 ] <= r + W + EPS )
		{
			chmin( nl, X[i] - W );
			chmax( nr, X[i] + W );
		}

		if ( nr + EPS < nl )
		{
			return false;
		}

		l = nl;
		r = nr;
	}

	return true;
}

int main()
{
	cin.tie( 0 );
	ios::sync_with_stdio( false );

	scanf( "%d", &N );
	REP( i, N )
	{
		scanf( "%d%d", T + i + 1, X + i + 1 );
	}

	double lb = 0, ub = INF;
	REP( i, 54 )
	{
		const double mid = ( lb + ub ) / 2;
		( possible( mid ) ? ub : lb ) = mid;
	}

	printf( "%.12lf\n", ub );
	fflush( stdout );

	return 0;
}

