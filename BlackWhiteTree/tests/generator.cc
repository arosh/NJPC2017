#include <iostream>
#include <utility>
#include "./testlib.h"
#include "./constraints.hpp"
#include <sys/types.h>
#include <unistd.h>

using namespace std;

#define rep(i,n) for(int i=0;i<(int)(n);i++)
#define rep2(i,a,b) for(int i=(int)(a);i<(int)(b);i++)

// aとbをファイルストリームに出力する
// ファイル名は prefix_num.in (ex: 00_sample_00.in)
void output(int N, const vector<int>& p, const vector<int> C, int Q, const vector<vector<int>> queries, const string &prefix, int num){
    cerr << "output" << endl;
    char name[100];
    sprintf(name, "%s_%02d.in", prefix.c_str(), num);
    ofstream ofs(name);
    ofs << N << endl;
    rep2(i, 1, N) {
        ofs << p[i] + 1 << endl;
    }
    rep(i, N) {
        ofs << C[i] << endl;
    }
    ofs << Q << endl;
    rep(i, Q) {
        rep(j, queries[i].size()) {
            ofs << (j ? " " : "") << queries[i][j] + 1;
        }
        ofs << endl;
    }
    ofs.close();
}

// 参考
// https://github.com/MikeMirzayanov/testlib/blob/master/generators/gen-rooted-tree-graph.cpp
// https://github.com/MikeMirzayanov/testlib/blob/master/generators/iwgen.cpp

// tはwnextのパラメータ
// rnd.wnext(i, t)は、0以上i以下の整数を|t|回サンプリングしたときのmax(t>0),min(t<0)を返す
// t = 0: random
// t > 0: 絶対値が大きいほどパスに近い(0-1-2-...)
// t < 0: 絶対値が大きいほどウニに近い(0が中心)
// |t| <= N で t をランダムに生成するとちょうど良さそう？
vector<int> makeTree(int n, int t) {
    cerr << "makeTree" << endl;
    vector<int> p(n);
    rep(i, n)
        if (i > 0)
            p[i] = rnd.wnext(i, t);

    vector<int> perm(n);
    rep(i, n)
        perm[i] = i;
    shuffle(perm.begin() + 1, perm.end());

    vector<int> pp(n);
    for (int i = 1; i < n; i++)
        pp[perm[i]] = perm[p[i]];

    return pp;
}

// a以上b以下の整数を重みwの乱数でn個生成し、vectorを返す
vector<int> genVector(int a, int b, int w, int n) {
    cerr << "genVector" << endl;
    vector<int> ret;
    rep(i, n) {
        ret.emplace_back(rnd.wnext(a, b, w));
    }
    return ret;
}

// N頂点の木に関するクエリをQ個生成
// ただし少なくとも1つは'2 u v'
vector<vector<int>> genQueries(int N, int Q) {
    cerr << "genQueries" << endl;
    cerr << "N = " << N << ", Q = " << Q << endl;
    vector<vector<int>> queries;
    int num_query_2 = rnd.next(1, Q);
    int num_query_1 = Q - num_query_2;
    cerr << num_query_1 << " " << num_query_2 << endl;
    rep(i, num_query_1) {
        // cerr << i << endl;
        // クエリ0('1 u' 色反転クエリ)
        int u = rnd.next(N - 1);
        queries.emplace_back(vector<int>{0, u});
    }
    rep(i, num_query_2) {
        // cerr << i << endl;
        // クエリ1('2 u v' 質問クエリ)
        int u = -1, v = -1;
        while (u == v) {
            u = rnd.next(0, N - 1);
            v = rnd.next(0, N - 1);
            cerr << "u = " << u << ", v = " << v << endl;
        }
        queries.emplace_back(vector<int>{1, u, v});
    }
    return queries;
}

int main(){
    // 乱数のシードを設定
    // pidを足すことで、1秒以上間を置かずに起動したときに同じシードになってしまうのを防ぐ
    rnd.setSeed(time(0)+getpid());

    // t = 0のランダムケースを10個生成
    for(int i = 0; i < 10; ++i){
        cerr << i << endl;
        int N = rnd.next(MIN_N, MAX_N);
        int t = 0;
        auto p = makeTree(N, t);
        auto C = genVector(0, 1, 0, N);
        int Q = rnd.next(MIN_Q, MAX_Q);
        auto queries = genQueries(N, Q);

        output(N, p, C, Q, queries, "10_random", i);

        // cerr << "N = " << N << ", t = " << t << endl;
        // rep(i, N) {
        //     cerr << (i ? " " : "") << p[i];
        // }
        // cerr << endl;

        // vector<int> deg(N);
        // rep2(i, 1, N) {
        //     deg[i]++;
        //     deg[p[i]]++;
        // }
        //
        // rep(i, N) {
        //     cerr << (i ? " " : "") << deg[i];
        // }
        // cerr << endl;
        // cerr << endl;
    }

    // // 片方が大きいケースを生成
    // for(int i = 0; i < 10; ++i){
    //     int A = 1;
    //     int B = 1;
    //     while(0.5*A <= B && B <= 1.5*A){
    //         A = rnd.next(MIN_A, MAX_A);
    //         B = rnd.next(MIN_B, MAX_B);
    //     }
    //     if(rnd.next(0,1)) swap(A, B);
    //     output(A, B, "60_unbalance", i);
    // }
}
