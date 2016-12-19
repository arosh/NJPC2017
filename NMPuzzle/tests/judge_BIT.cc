#include "testlib.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define rep2(i, a, b) for (int i = int(a); i < int(b); i++)
#define rrep(i,n) for (int i=(n)-1;i>=0;i--)
#define rrep2(i,a,b) for (int i=(a)-1;i>=b;i--)

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

class Bit {
private:
    vector<int> bit;
    const int n;

public:
    Bit(int _n) : n(_n), bit(_n + 1, 0) {}

    // get sum in [1, i]
    // sum{[i, j]} = sum{[1, j]} - sum{[1, i-1]}
    int sum(int i) {
        int s = 0;
        while (i > 0) {
            s += bit[i];
            i -= i & -i;
        }
        return s;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    // add x to bit[i]
    void add(int i, int x) {
        while (i <= n) {
            bit[i] += x;
            i += i & -i;
        }
    }
};

// O(N^2logN) BIT ver.
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
            Bit bit(M);
            map<int, int> mp;
            rep(j, M) {
                mp[a[i][j]] = 0;
            }
            int num = 1;
            for (auto& p : mp) {
                p.second = num++;
            }

            // 右から処理
            rrep(j, M) {
                int x = mp[a[i][j]];
                score += bit.sum(x);
                bit.add(x, 1);
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
