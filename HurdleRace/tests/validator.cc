#include "./testlib.h"
#include "./constraints.hpp"
#include <cassert>
#include <vector>
using namespace std;

int main(){
    registerValidation();
    int N = inf.readInt(MIN_N, MAX_N);
    inf.readSpace();
    inf.readInt(MIN_L, MAX_L);
    inf.readEoln();
    vector<int> X(N);
    for (int i = 0; i < N; i++) {
      X[i] = inf.readInt(MIN_Xi, MAX_Xi);
      inf.readEoln();
      if (i > 0) {
        assert(X[i] > X[i - 1]);
      }
    }
    inf.readEof();
}
