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

void gen_random( ostream & out,
		const int min_n = MIN_N, const int max_n = MAX_N,
		const int min_d = MIN_D, const int max_d = MAX_D,
		const int min_c = MIN_C, const int max_c = MAX_C )
{
	const int N = rng.next( min_n, max_n );
	const int D = rng.next( min_d, max_d );

	out << N << ' ' << D << '\n';

	for ( int i = 1; i < N; ++i )
	{
		int u = i, v = rng.next( 0, i - 1 );
		if ( rng.next( 0, 1 ) )
		{
			swap( u, v );
		}

		const int c = rng.next( min_c, max_c );
		out << u + 1 << ' ' << v + 1 << ' ' << c << '\n';
	}
	out << flush;

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
			gen_random( out );
		}
	}

	return 0;
}
