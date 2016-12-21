#include "./testlib.h"
#include "./constraints.hpp"
#include <cassert>
#include <vector>

int main(){
    registerValidation();
    int N =  inf.readInt(MIN_N, MAX_N);
    inf.readEoln();

    std::vector<int> T(N);
    for(int i=0;i<N;i++){
    	T[i] = inf.readInt(MIN_Ti,MAX_Ti);
    	inf.readSpace();
    	inf.readInt(MIN_Xi,MAX_Xi);
    	inf.readEoln();
    }
    inf.readEof();

    for(int i=0;i<N-1;i++){
    	assert(T[i]<T[i+1]);
    }
}
