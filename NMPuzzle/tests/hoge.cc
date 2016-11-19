#include "testlib.h"
#include <iostream>
#include <vector>

using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define rep2(i, a, b) for (int i = int(a); i < int(b); i++)

int main(int argc, char * argv[])
{
    int N = 2, M = 3, K = 5;
    vector<vector<int>> a(N, vector<int>(M));
    rep(i, N) rep(j, M) cin >> a[i][j];

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
        vector<vector<int>> b(M, vector<int>(N));
        rep(i, M) rep(j, N) b[i][j] = a[j][i];
        a = b;
        swap(N, M);
    }

    cout << score << endl;
}
