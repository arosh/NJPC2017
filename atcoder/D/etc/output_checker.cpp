#include "testlib.h"
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define rep2(i, a, b) for (int i = int(a); i < int(b); i++)

vector<vector<int> > readIntTable(InStream& in, TResult pe, int n, int m) {
    vector<vector<int> > ret(n, vector<int>(m));
    rep(i, n) {
        rep(j, m) {
            ret[i][j] = in.readInt();
            if (j < m - 1) {
                in.readSpace();
            }
        }
        in.readEoln();
    }
    in.readEof();
    return ret;
}

// O(N^3)実装
int main(int argc, char * argv[])
{
    setName("check if the score of participant's answer is exactly K");

    // registerTestlibCmd(argc, argv);
    // 引数の順番やら何やらが違うので以下を使う
    inf.init(argv[2], _input);
    ans.init(argv[4], _answer);
    ouf.init(argv[6], _output);

    int N = inf.readInt();
    inf.readSpace();
    int M = inf.readInt();
    inf.readSpace();
    int K = inf.readInt();
    inf.readEoln();
    inf.readEof();

    // participantの出力
    vector<vector<int> > a = readIntTable(ouf, _pe, N, M);
    // 想定出力ファイルは使わない

    // 出力が1からNMまでのdistinctな整数になっているか判定
    vector<bool> exist(N * M + 1);
    rep(i, N) {
        rep(j, M) {
            if (a[i][j] < 1 || N * M < a[i][j] || exist[a[i][j]]) {
                quitf(_wa, "invalid element exists");
            }
            exist[a[i][j]] = true;
        }
    }

    // スコアの計算
    int score = 0;
    rep(t, 2) {
        // 各行の転倒数の和をとる
        rep(i, N) {
            rep(j, M) {
                rep2(k, j + 1, M) {
                    if (a[i][j] > a[i][k]) {
                        score++;
                    }
                }
            }
        }

        if (t == 1) break;

        // 転置
        vector<vector<int> > b(M, vector<int>(N));
        rep(i, M) rep(j, N) b[i][j] = a[j][i];
        a = b;
        swap(N, M);
    }

    if (score == K) {
        quitf(_ok, "score is %d", score);
    } else {
        quitf(_wa, "expected score is %d, but calculated score is %d", K, score);
    }
}
