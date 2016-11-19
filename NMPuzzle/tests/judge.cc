#include "testlib.h"
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define rep2(i, a, b) for (int i = int(a); i < int(b); i++)

vector<vector<int> > readIntTable(InStream& in, TResult pe, int n, int m) {
    // TODO: 出力制約を満たしているか(行列のサイズ、1..NMの数字がdistinctに出現, etc...)
    vector<vector<int> > ret(n, vector<int>(m));
    rep(i, n) {
        rep(j, m) {
            ret[i][j] = in.readInt();
            cout << "i = " << i << ", " << j << endl;
            if (j < m - 1) {
                in.readSpace();
            }
        }
        cout << i << endl;

        in.readEoln();
    }
    in.readEof();
    return ret;
}

int main(int argc, char * argv[])
{

    setName("check if the score of participant's answer is exactly K");

    // registerTestlibCmd(argc, argv);
    // 引数の順番やら何やらが違うので以下を使う

    cout << argc << endl;
    rep(i, argc) {
        cout << argv[i] << endl;
    }

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

    cout << "hey!" << endl;

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

    cout << "hey!" << endl;

    if (score == K) {
        return 0;
    } else {
        return 1;
    }
}
