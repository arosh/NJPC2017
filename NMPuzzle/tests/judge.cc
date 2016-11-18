#include "testlib.h"
#include <stdio.h>
#include <vector>

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define rep2(i, a, b) for (int i = int(a); i < int(b); i++)

vector<vector<int>> readIntTable(InStream& in, TResult pe, int n, int m) {
    // TODO: 出力制約を満たしているか(行列のサイズ、1..NMの数字がdistinctに出現, etc...)
    vector<vector<int>> ret;
    rep(i, n) {
        rep(j, m) {
            ret[i][j] = in.readInt();
            if (j < m) in.readSpace();
        }
        in.readEoln();
    }
    in.readEof();
    return ret;
}

int main(int argc, char * argv[])
{
    setName("check if the score of participant's answer is exactly K");
    registerTestlibCmd(argc, argv);

    int N = inf.readInt();
    inf.readSpace();
    int M = inf.readInt();
    inf.readSpace();
    int K = inf.readInt();
    inf.readEoln();
    inf.readEof();

    // participantの出力
    vector<vector<int>> a = readIntTable(ouf, _pe, N, M);
    // 想定出力ファイルは使わない

    // スコアの計算
    int score = 0;
    rep(i, N) {
        rep(j, M) {
            rep2(k, j + 1, M) {
                if (a[i][j] > a[i][k]) {
                    score++;
                }
            }
        }
    }

    if (score == K) {
        quitf(_ok, "score is %d", K);
    } else {
        quitf(_wa, "expected score is %d, but participant's score is %d", K, score);
    }
}
