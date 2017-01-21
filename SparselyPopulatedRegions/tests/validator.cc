#include "./testlib.h"
#include "./constraints.hpp"
#include <cassert>
#include <vector>
#include <set>
using namespace std;

class UnionFind {
private:
    const int n;
    vector<int> uni;
public:
    UnionFind(int _n) : n(_n), uni(_n, -1) {}
    int root(int x) {
        if (uni[x] < 0) return x;
        return uni[x] = root(uni[x]);
    }
    bool same(int x, int y) {
        return root(x) == root(y);
    }
    bool unite(int x, int y) {
        x = root(x);
        y = root(y);
        if (x == y) return false;
        if (uni[x] > uni[y]) swap(x, y);
        uni[x] += uni[y];
        uni[y] = x;
        return true;
    }
};

int main(){
    registerValidation();
    int N = inf.readInt(MIN_N, MAX_N);
    inf.readSpace();
    int D = inf.readInt(MIN_D, MAX_D);
    inf.readEoln();
    std::vector<int> A(N-1), B(N-1), C(N-1);
    // set<set<int>> st;
    set<pair<int, int>> st;
    UnionFind uf(N);
    for(int i=0;i<N-1;i++){
      A[i] = inf.readInt(MIN_AB, N);
      inf.readSpace();
      B[i] = inf.readInt(MIN_AB, N);
      inf.readSpace();
      C[i] = inf.readInt(MIN_C, MAX_C);
      inf.readEoln();

      assert(A[i] != B[i]);
    //   assert(!st.count(set<int>{A[i], B[i]}));
      assert(!st.count(make_pair(A[i], B[i])) && !st.count(make_pair(B[i], A[i])));
      st.insert(make_pair(A[i], B[i]));
      assert(uf.unite(A[i]-1, B[i]-1));
    }

    /*
    for(int i=0;i<N-1;i++){
      assert(A[i]!=B[i]);
      for(int j=0;j<N-1;j++){
        if(i==j) continue;
        assert(A[i]==A[j]&&B[i]==B[j]);
        assert(A[i]==B[j]&&A[j]==B[i]);
      }
    }
    */

    inf.readEof();
}
