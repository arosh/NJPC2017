#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;

#define rep(i,n) for (int i=0;i<(n);i++)
#define all(a) (a).begin(),(a).end()

// AC: ジャンプと着地の位置は地上扱い

// 部分点 DP

/*
    bool dp[i] = (位置 x = i + ε でジャンプできる状態であるとき、x > i のハードルを全て飛び越すことができるか？)

    max(x_j) <= i のとき:
        dp[i] = true
    i < max(x_j) のとき:
        dp[i] = ((empty(i, j] && dp[j]) または (empty(i, j] && empty(j + L, j + 2L] && dp[j + 2L])) なる j >= i が存在すればtrue, そうでなければfalse

    ただし、empty(l, r] := l < x <= r の範囲にハードルが存在しなければtrue, そうでなければfalse

    状態数O(max(x_i)), 一つの状態に対して遷移がO(max(x_i))通り
    empty[l, r]は累積和を用いてO(1)で判定できる
    全体でO(max(x_i)^2)
*/

const int MAX_Xi = 10000;

int N, L;
int ma_x;
int S[MAX_Xi];
bool dp[MAX_Xi];
bool visited[MAX_Xi];

// (l, r]
bool empty(int l, int r) {
    r++;
    if (l >= r) return true;
    return S[l] - S[r] == 0;
}

bool f(int i) {
    if (i >= ma_x) return true;
    if (visited[i]) return dp[i];
    visited[i] = true;
    for (int j = i; j <= ma_x; ++j) {
        if (!empty(i, j)) break;
        // ジャンプしないとき
        dp[i] |= f(j);
        // ジャンプするとき
        dp[i] |= empty(j + L, j + 2 * L) && f(j + 2 * L);
    }
    return dp[i];
}

int main() {
    cin >> N >> L;
    rep(i, N) {
        int x;
        cin >> x;
        ma_x = max(ma_x, x);
        S[x]++;
    }

    for (int i = ma_x; i >= 0; --i) {
        S[i] += S[i + 1];
    }

    cout << (f(0) ? "YES" : "NO") << endl;

    cerr << "dp result:" << endl;
    rep(i, ma_x + 1) {
        cerr << i << ": " << dp[i] << endl;
    }

}
