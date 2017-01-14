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

int main()
{
	rng.setSeed( 711 );

	{ // random
		FileName fname( 1, "random" );
		for ( int i = 0; i < 10; ++i )
		{
			ofstream out( fname() );
			gen_random( out, MIN_L, MAX_L, rng.next( 'a', 'z' ), 'z' );
		}
	}

	{ // large
		FileName fname( 2, "random_large" );
		for ( int i = 0; i < 10; ++i )
		{
			ofstream out( fname() );
			gen_random( out, MAX_L - rng.next( 0, 100 ), MAX_L, rng.next( 'a', 'z' ), 'z' );
		}
	}

	{ // maximal
		FileName fname( 3, "maximal" );
		for ( int i = 0; i < 5; ++i )
		{
			ofstream out( fname() );
			gen_random( out, MAX_L, MAX_L, rng.next( 'a', 'z' ), 'z' );
		}
	}

	return 0;
}
