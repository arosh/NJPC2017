// Problem : CommutativeLaw
// Author : torus711
// Expected : AC?
// Complexity : ???

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

#include <type_traits>

template < typename T, int depth,
		 typename enable_if< depth == 0, nullptr_t >::type = nullptr >
bool solve( const VT< T > & )
{
	return true;
}

template < typename T, int depth = 50,
		 typename enable_if< depth, nullptr_t >::type = nullptr >
bool solve( const VT< T > &A )
{
	const int N = SZ( A );

	const T mi = *min_element( ALL( A ) );
	if ( A[0] != mi )
	{
		return false;
	}

	VI ps( 1 );
	REP( i, 1, N )
	{
		if ( A[ i - 1 ] != mi && A[i] == mi )
		{
			ps.PB( i );
		}
	}

	if ( SZ( ps ) == 1 )
	{
		return true;
	}
	ps.PB( N );

	VVT< T > B;
	REP( i, SZ( ps ) - 1 )
	{
		B.EB( begin( A ) + ps[i] + 1, begin( A ) + ps[ i + 1 ] );
	}

	return solve< VT< T >, depth - 1 >( B );
}

int main()
{
	cin.tie( 0 );
	ios::sync_with_stdio( false );

	string S;
	cin >> S;

	cout << ( solve( VT< char >( ALL( S ) ) ) ? "Yes" : "No" ) << endl;

	return 0;
}
