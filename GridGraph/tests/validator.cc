#include "./testlib.h"
#include "./constraints.hpp"
#include <cassert>
#include <utility>
#include <set>
using namespace std;

typedef pair<int,int> pii;

int main(){
    registerValidation();
    int H,W,N;
    H = inf.readInt(MIN_H, MAX_H);
    inf.readSpace();
    W = inf.readInt(MIN_W, MAX_W);
    inf.readSpace();
    N = inf.readInt(MIN_N, MAX_N);
    inf.readEoln();

    set<pii> st;
    for(int i=0;i<N;i++){
    	int r,c;
    	r = inf.readInt(MIN_H,H);
    	inf.readSpace();
    	c = inf.readInt(MIN_W,W);
    	inf.readEoln();

    	st.insert(pii(r,c));
    }
    assert(N==st.size());

    inf.readEof();
}
