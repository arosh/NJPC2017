#include <iostream>
#include <utility>
#include "./testlib.h"
#include "./constraints.hpp"
#include <sys/types.h>
#include <unistd.h>
#include <cassert>
#include <map>
#include <cmath>

using namespace std;

#define rep(i,n) for(int i=0;i<(int)(n);i++)
#define rep2(i,a,b) for(int i=(int)(a);i<(int)(b);i++)

// aとbをファイルストリームに出力する
// ファイル名は prefix_num.in (ex: 00_sample_00.in)
void output(int N, const vector<int>& p, const vector<int> C, int Q, const vector<vector<int>> queries, const string &prefix, int num = 0){
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

// 根つき木を表す頂点のリストを受け取り、頂点番号をシャッフルする
vector<int> permVertexList(const vector<int>& p) {
    int n = p.size();
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
// n1, n2でクエリ1, 2の個数を指定(-1, -1の場合はランダム)
vector<vector<int>> genQueries(int N, int Q, int n1 = -1, int n2 = -1, int e = -1) {
    cerr << "genQueries" << endl;
    cerr << "N = " << N << ", Q = " << Q << endl;
    vector<vector<int>> queries;
    if (n1 == -1 && n2 == -1) {
        // クエリ1とクエリ2の比率の桁数がランダムになるようにする
        n2 = rnd.next(MIN_Q, Q / (int)pow(10, (e != -1 ? e : rnd.next(0, (int)log10(Q)))));
        n1 = Q - n2;
    }
    else {
        assert(0 <= n1 && n1 <= Q);
        assert(1 <= n2 && n2 <= Q);
        assert(n1 + n2 == Q);
    }
    cerr << n1 << " " << n2 << endl;
    rep(i, n1) {
        // cerr << i << endl;
        // クエリ0('1 u' 色反転クエリ)
        int u = rnd.next(N - 1);
        queries.emplace_back(vector<int>{0, u});
    }
    rep(i, n2) {
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
    shuffle(queries.begin(), queries.end());
    return queries;
}

// 頂点nowからstep個前の親までのパスを交互に塗る
// 頂点0(根)に到達したらそこで終了
void coloringPath(int now, int step, int color, const vector<int>& p, vector<int>& C) {
    C[now] = color;
    if (now == 0 || step == 0) return;
    coloringPath(p[now], step - 1, color ^ 1, p, C);
}

// 幾つかのパスを選んで交互に塗る
void coloringPath(const vector<int>& p, vector<int>& C) {
    int N = p.size();
    rep(i, rnd.next(1, 100)) {
        coloringPath(rnd.next(0, N - 1), rnd.next(1, N), rnd.next(0, 1), p, C);
    }
}

using Graph = vector<vector<int>>;

// dfs
void coloringTreeAlternately(int now, int pre, int color, const Graph& G, vector<int>& C) {
    C[now] = color;
    for (auto nxt : G[now]) {
        if (nxt == pre) continue;
        coloringTreeAlternately(nxt, now, color ^ 1, G, C);
    }
}

// 木全体を交互に塗る
void coloringTreeAlternately(const vector<int>& p, vector<int>& C) {
    int N = p.size();
    Graph G(N);
    rep2(i, 1, N) {
        G[i].emplace_back(p[i]);
        G[p[i]].emplace_back(i);
    }
    coloringTreeAlternately(0, -1, rnd.next(0, 1), G, C);
}

int main(){
    // 乱数のシードを設定
    // pidを足すことで、1秒以上間を置かずに起動したときに同じシードになってしまうのを防ぐ
    // rnd.setSeed(time(0)+getpid());
    rnd.setSeed(711);

    /*
    // 検証用
    rep(_i, 10) {
        int N = rnd.next(MIN_N, MAX_N);
        int t = rnd.next(-1 * rnd.next(0, N) / pow(10, rnd.next(0, 5)), rnd.next(0, N) / pow(10, rnd.next(0, 5)));
        auto p = makeTree(N, t);

        cerr << "N = " << N << ", t = " << t << endl;

        vector<int> deg(N);
        rep2(i, 1, N) {
            deg[i]++;
            deg[p[i]]++;
        }

        map<int, int> deg2freq;
        rep(i, N) {
            deg2freq[deg[i]]++;
        }

        vector<int> freq;
        for (auto p : deg2freq) {
            freq.emplace_back(p.second);
        }
        sort(freq.rbegin(), freq.rend());

        rep(i, min<int>(10, freq.size())) {
            cerr << (i ? " " : "") << freq[i];
        }
        cerr << endl;
    }
    */


    rep(k, 10) {
        int N = rnd.next(MIN_N, MAX_N);
        int t = rnd.next(-1 * rnd.next(0, N) / pow(10, rnd.next(0, 5)), rnd.next(0, N) / pow(10, rnd.next(0, 5)));
        auto p = makeTree(N, t);
        auto C = genVector(0, 1, 0, N);
        int Q = rnd.next(MIN_Q, MAX_Q);
        auto queries = genQueries(N, Q);

        output(N, p, C, Q, queries, "01_graph_random_color_random_query_random", k);
    }

    rep(k, 10) {
        int N = rnd.next(MIN_N, MAX_N);
        int t = rnd.next(-1 * rnd.next(0, N) / pow(10, rnd.next(0, 5)), rnd.next(0, N) / pow(10, rnd.next(0, 5)));
        auto p = makeTree(N, t);
        vector<int> C(N, rnd.next(0, 1));
        int Q = rnd.next(MIN_Q, MAX_Q);
        auto queries = genQueries(N, Q);

        output(N, p, C, Q, queries, "02_graph_random_color_same_query_random", k);
    }

    rep(k, 10) {
        int N = rnd.next(MIN_N, MAX_N);
        int t = rnd.next(-1 * rnd.next(0, N) / pow(10, rnd.next(0, 5)), rnd.next(0, N) / pow(10, rnd.next(0, 5)));
        auto p = makeTree(N, t);
        vector<int> C(N);
        coloringTreeAlternately(p, C);
        int Q = rnd.next(MIN_Q, MAX_Q);
        auto queries = genQueries(N, Q);

        output(N, p, C, Q, queries, "03_graph_random_color_alternate_query_random", k);
    }

    /*

    // t = 0のランダムグラフ
    {
        // 全てランダムなケースを10個生成
        for(int k = 0; k < 10; ++k){
            int N = rnd.next(MIN_N, MAX_N);
            int t = 0;
            auto p = makeTree(N, t);
            auto C = genVector(0, 1, 0, N);
            int Q = rnd.next(MIN_Q, MAX_Q);
            auto queries = genQueries(N, Q);

            output(N, p, C, Q, queries, "03_graph_random_color_random_query_random", k);
        }


        // 色交互から幾つかのパスを交互に塗り替えたケースを5個生成
        for(int k = 0; k < 10; ++k){
            int N = rnd.next(MIN_N, MAX_N);
            int t = 0;
            auto p = makeTree(N, t);
            vector<int> C(N);
            coloringTreeAlternately(p, C);
            coloringPath(p, C);
            int Q = rnd.next(MIN_Q, MAX_Q);
            auto queries = genQueries(N, Q);

            output(N, p, C, Q, queries, "01_graph_random_color_alter_query_random", k);
        }

        // 色ランダムから幾つかのパスを交互に塗り替えたケースを5個生成
        for(int k = 0; k < 10; ++k){
            int N = rnd.next(MIN_N, MAX_N);
            int t = 0;
            auto p = makeTree(N, t);
            auto C = genVector(0, 1, 0, N);
            coloringPath(p, C);
            int Q = rnd.next(MIN_Q, MAX_Q);
            auto queries = genQueries(N, Q);

            output(N, p, C, Q, queries, "02_graph_random_color_random2alter_query_random", k);

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

    }

    */

    // graph_path (0 - 1 - 2 - ... - (N-1))
    {
        int N = MAX_N;
        vector<int> p(N);
        rep2(i, 1, N) p[i] = i - 1;
        int Q = MAX_Q;

        // 色・クエリランダム
        for (int k = 0; k <= 5; ++k) {
            auto C = genVector(0, 1, 0, N);
            auto queries = genQueries(N, Q, -1, -1, k);
            output(N, p, C, Q, queries, "10_graph_path_color_random_query_random", k);
        }

        // 白黒交互, クエリ2のみ -> 常にYES
        {
            vector<int> C(N);
            rep(i, N) C[i] = i % 2;
            auto queries = genQueries(N, Q, 0, Q);

            output(N, p, C, Q, queries, "10_graph_path_color_alternate_query_all2");
        }

        // 全て同じ色, クエリ2のみ -> 常にNO
        {
            vector<int> C(N, rnd.next(0, 1));
            auto queries = genQueries(N, Q, 0, Q);

            output(N, p, C, Q, queries, "10_graph_path_color_same_query_all2");
        }

        // 全て同じ色, 交互に塗り替え -> 最後のクエリ2のみYES
        {
            vector<int> C(N, rnd.next(0, 1));
            vector<vector<int>> queries;
            for (int i = N - 1; i > 0; --i) {
                queries.emplace_back(vector<int>{0, i});
            }
            queries.emplace_back(vector<int>{1, 0, N - 1});

            output(N, p, C, Q, queries, "10_graph_path_color_sametoAlternate_query_11...12");
        }

        // // 色00...011...1, クエリ1は境目以外 -> 境目を{a,b}として、'2 a b' のみYES
        // {
        //     vector<int> C(N);
        //     int a = rnd.next(0, N - 1);
        //     int b = a + 1;
        //     vector<vector<int>> queries;
        //     rep(i, Q) {
        //         if (!rnd.next(0, 1)) {
        //
        //         }
        //     }
        //
        //     output(N, p, C, Q, queries, "graph_path_color_00...011...1_query_mostlyrandom");
        // }
    }

    // graph_star (1 - {0, 2, 3, 4, ...})
    //        0
    //        |
    // 2 - center - 3
    //        |
    //        4
    {
        int N = MAX_N;
        int Q = MAX_Q;

        // 色・クエリランダム
        for (int k = 0; k <= 5; ++k) {
            vector<int> p(N);
            int center = rnd.next(0, N - 1);
            rep2(i, 1, N) p[i] = (i == center ? 0 : center);

            auto C = genVector(0, 1, 0, N);
            auto queries = genQueries(N, Q, -1, -1, k);

            output(N, p, C, Q, queries, "20_graph_star_color_random_query_random", k);
        }

        // 白黒交互, クエリ2のみ -> 常にYES
        {
            vector<int> p(N);
            int center = rnd.next(0, N - 1);
            rep2(i, 1, N) p[i] = (i == center ? 0 : center);

            vector<int> C(N);
            C[center] = 1;
            auto queries = genQueries(N, Q, 0, Q);

            output(N, p, C, Q, queries, "20_graph_star_color_alternate_query_all2");
        }

        // 全て同じ色, クエリ2のみ -> 常にNO
        {
            vector<int> p(N);
            int center = rnd.next(0, N - 1);
            rep2(i, 1, N) p[i] = (i == center ? 0 : center);

            vector<int> C(N, rnd.next(0, 1));
            auto queries = genQueries(N, Q, 0, Q);

            output(N, p, C, Q, queries, "20_graph_star_color_same_query_all2");
        }

        // 全て同じ色, 交互に塗り替え -> 最後のクエリ2のみYES
        {
            vector<int> p(N);
            int center = rnd.next(0, N - 1);
            rep2(i, 1, N) p[i] = (i == center ? 0 : center);

            vector<int> C(N, rnd.next(0, 1));
            vector<vector<int>> queries;
            for (int i = N - 1; i > 0; --i) {
                queries.emplace_back(vector<int>{0, i});
            }
            queries.emplace_back(vector<int>{1, 0, N - 1});

            output(N, p, C, Q, queries, "20_graph_star_color_sametoAlternate_query_11...12");
        }

        // ウニの中心を塗り替えまくる
        rep(k, 11) { // クエリ1の比率 = 1 - k / 10
            vector<int> p(N);
            int center = rnd.next(0, N - 1);
            rep2(i, 1, N) p[i] = (i == center ? 0 : center);

            auto C = genVector(0, 1, 0, N);
            vector<vector<int>> queries;
            int n2 = max(MIN_Q, Q - k * (Q / 10));
            int n1 = Q - n2;
            rep(i, n1) {
                queries.emplace_back(vector<int>{0, center});
            }
            rep(i, n2) {
                int u = -1, v = -1;
                while (u == v) {
                    u = rnd.next(0, N - 1);
                    v = rnd.next(0, N - 1);
                }
                queries.emplace_back(vector<int>{1, u, v});
            }
            shuffle(queries.begin(), queries.end());

            output(N, p, C, Q, queries, "20_graph_star_color_random_query_1Center2random", k);
        }
    }

    // graph_hitode
    // ある頂点centerから幾つかのパスが伸びているグラフ
    {
        int N = MAX_N;
        int Q = MAX_Q;

        // 色・クエリランダム
        for (int k = 0; k <= 5; ++k) {
            vector<int> p(N);
            int num_path = min(3, 10 * (k + 1)); // パスの本数は10, 100, 1000
            vector<int> leaf(num_path + 1); // leaf[i] = i番目のパスの葉 (!!iは1-indexed!!)
            rep2(i, 1, num_path + 1) {
                // 1, 2, ..., num_path が最初の葉
                p[i] = 0;
                leaf[i] = i;
            }
            rep2(i, num_path + 1, N) {
                // ランダムに選んだ葉をiの親とし、iが新たな葉になる
                int t = rnd.next(1, num_path);
                p[i] = leaf[t];
                leaf[t] = i;
            }

            // 頂点をシャッフル
            vector<int> perm(N);
            rep(i, N) perm[i] = i;
            shuffle(perm.begin() + 1, perm.end()); // 0が根であることは変えてはならない

            vector<int> pp(N);
            for (int i = 1; i < N; i++)
                pp[perm[i]] = perm[p[i]];

            p = std::move(pp);

            auto C = genVector(0, 1, 0, N);
            auto queries = genQueries(N, Q, -1, -1, k);

            output(N, p, C, Q, queries, "30_graph_hitode_color_random_query_random", k);
        }
    }

    // graph_caterpillar
    // パスに頂点を刺しまくった木
    {
        int N = MAX_N;
        int Q = MAX_Q;

        // 色・クエリランダム
        for (int k = 0; k <= 5; ++k) {
            vector<int> p(N);
            int len_path = min(5, 100 * (k + 1)); // パスの長さ(頂点数)は100, 1000, 10000
            rep2(i, 1, len_path) {
                // 0 - 1 - ... - (len_path - 1)
                p[i] = i - 1;
            }
            rep2(i, len_path, N) {
                // パスから頂点をランダムに選び、iの親とする
                p[i] = rnd.next(0, len_path - 1);
            }
            p = permVertexList(p);
            auto C = genVector(0, 1, 0, N);
            auto queries = genQueries(N, Q, -1, -1, k);

            output(N, p, C, Q, queries, "40_graph_caterpillar_color_random_query_random", k);
        }
    }

    // graph_binaryTree
    {
        int N = MAX_N;
        int Q = MAX_Q;

        // 色・クエリランダム
        for (int k = 0; k <= 5; ++k) {
            vector<int> p(N);
            rep2(i, 1, N) {
                p[i] = (i - 1) / 2;
            }
            p = permVertexList(p);
            auto C = genVector(0, 1, 0, N);
            auto queries = genQueries(N, Q, -1, -1, k);

            output(N, p, C, Q, queries, "50_graph_binaryTree_color_random_query_random", k);
        }
    }

    // graph_ternaryTree
    {
        int N = MAX_N;
        int Q = MAX_Q;

        // 色・クエリランダム
        for (int k = 0; k <= 5; ++k) {
            vector<int> p(N);
            rep2(i, 1, N) {
                p[i] = (i - 1) / 3;
            }
            p = permVertexList(p);
            auto C = genVector(0, 1, 0, N);
            auto queries = genQueries(N, Q, -1, -1, k);

            output(N, p, C, Q, queries, "60_graph_ternaryTree_color_random_query_random", k);
        }
    }

    // graph_triangle
    //           0
    //          / ¥
    //         1   2
    //        /    / ¥
    //       3    4   5
    //      /    /   / ¥
    //     6    7   8   9
    {
        int N = MAX_N;
        int Q = MAX_Q;

        // 色・クエリランダム
        for (int k = 0; k <= 5; ++k) {
            vector<int> p(N);
            int i = 1;
            for (int t = 1; t * (t + 1) / 2 < N; t++) {
                rep(j, t) {
                    p[i] = i - t;
                    i++;
                }
                p[i] = i - t - 1;
                i++;
            }
            p = permVertexList(p);
            auto C = genVector(0, 1, 0, N);
            auto queries = genQueries(N, Q, -1, -1, k);

            output(N, p, C, Q, queries, "70_graph_triangle_color_random_query_random", k);
        }
    }

}
