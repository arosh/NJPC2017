#include <bits/stdc++.h>

#include "./testlib.h"
#include "./constraints.hpp"

using namespace std;

random_t rng;

struct FileName
{
	const int id;
	const string name;
	int done = 0;

	FileName( const int id, const string name ) :
		id( id ), name( name )
	{
		return;
	}

	string operator()()
	{
		ostringstream oss;
		oss << setfill( '0' ) << setw( 2 ) << id << '_' << name << '_' << setw( 2 ) << done++ << ".in";
		return move( oss.str() );
	}
};

void gen_random( ostream & out, const int min_l, const int max_l, const char min_c = 'a', const char max_c = 'z' )
{
	const int L = rng.next( min_l, max_l );

	string S;
	generate_n( back_inserter( S ), L, [&]{ return rng.next( min_c, max_c ); } );

	out << S << endl;

	return;
}

void gen_fibonacci( ostream &out,
		const int min_l, const int max_l,
		const char a = 'a', const char b = 'b' )
{
	const int L = rng.next( min_l, max_l );

	string S1( 1, a ), S2( 1, b ), S3;

	while ( S1.size() + S2.size() <= L )
	{
		const string &&S = S1 + S2;
		S1 = S2;
		S2 = S3;
		S3 = S;
	}

	out << S3 << endl;

	return;
}

int main()
{
	// rng.setSeed( 711 );
	rng.setSeed(time(0));

	const int NUM_CASES = 1000;



	{ // random
		FileName fname( 1, "random" );
		for ( int i = 0; i < NUM_CASES; ++i )
		{
			ofstream out( fname() );
			gen_random( out, MIN_L, MAX_L, rng.next( 'a', 'z' ), 'z' );
		}
	}

	{ // large
		FileName fname( 2, "random_large" );
		for ( int i = 0; i < NUM_CASES; ++i )
		{
			ofstream out( fname() );
			gen_random( out, MAX_L - rng.next( 0, 100 ), MAX_L, rng.next( 'a', 'z' ), 'z' );
		}
	}

	{ // maximal
		FileName fname( 3, "maximal" );
		for ( int i = 0; i < NUM_CASES; ++i )
		{
			ofstream out( fname() );
			gen_random( out, MAX_L, MAX_L, rng.next( 'a', 'z' ), 'z' );
		}
	}

	{ // fibonacci
		FileName fname( 4, "fibonacci" );
		for ( int i = 0; i < NUM_CASES; ++i )
		{
			ofstream out( fname() );
			gen_fibonacci( out, MAX_L, MAX_L, rng.next( 'a', 'z' ), rng.next( 'a', 'z' ) );
		}
	}

	{ // single
		FileName fname( 5, "single" );
		for ( int i = 0; i < NUM_CASES; ++i )
		{
			ofstream out( fname() );
			const char c = rng.next( 'a', 'z' );
			gen_random( out, MAX_L, MAX_L, c, c );
		}
	}

	return 0;
}
