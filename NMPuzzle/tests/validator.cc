#include "./testlib.h"
#include "./constraints.hpp"
#include <cassert>

int main(){
    registerValidation();
    inf.readInt(MIN_N, MAX_N);
    inf.readSpace();
    inf.readInt(MIN_M, MAX_M);
    inf.readSpace();
    const int MAX_K = MAX_N * MAX_M * (MAX_M - 1) / 2 + MAX_M * MAX_N * (MAX_N - 1) / 2;
    inf.readInt(MIN_K, MAX_K);
    inf.readEoln();
    inf.readEof();
}
