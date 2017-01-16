#include "./testlib.h"
#include "./constraints.hpp"
#include <cassert>
#include <vector>

int main(){
    registerValidation();
    int N = inf.readInt(MIN_N, MAX_N);
    inf.readSpace();
    int D = inf.readInt(MIN_D, MAX_D);
    inf.readEoln();
    std::vector<int> A(n-1), B(n-1), C(n-1);
    for(int i=0;i<N-1;i++){
      A[i] = inf.readInt(MIN_AB, N)
      inf.readSpace();
      B[i] = inf.readInt(MIN_AB, N)
      inf.readSpace();
      C[i] = inf.readInt(MIN_C, MAX_C)
      inf.readEoln();
    }
    for(int i=0;i<N-1;i++){
      assert(A[i]!=B[i]);
      for(int j=0;j<N-1;j++){
        if(i==j) continue;
        assert(A[i]==A[j]&&B[i]==B[j]);
        assert(A[i]==B[j]&&A[j]==B[i]);
      }
    }
    inf.readEof();
}
