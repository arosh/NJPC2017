#include <iostream>
#include <algorithm>
using namespace std;

#define rep(i,n) for (int i=0;i<(n);i++)
#define all(a) (a).begin(),(a).end()

// WA: ジャンプor着地する位置が空中扱い

// 部分点 DP

/*
    bool dp[i] = (位置 x = i でジャンプできる状態であるとき、x > i のハードルを全て飛び越すことができるか？)

    max(x_i) < i のとき:
        dp[i] = true
    i <= max(x_i) のとき:
        dp[i] = ((empty(i - 1, j) && dp[j]) または (empty(i - 1, j) && empty(j + L, j + 2L) && dp[j + 2L])) なる j >= i が存在すればtrue, そうでなければfalse

    ただし、empty(l, r) := (l < x < rの範囲にハードルが存在しなければtrue, そうでなければfalse)
    x=iにハードルがあればx=iでジャンプしなければならないことに注意(dp[i]の定義より、そのようなハードルはまだ飛んでいない)

    状態数O(max(x_i)), 一つの状態に対して遷移がO(max(x_i))通り
    empty(l, r)は累積和を用いてO(1)で判定できる
    全体でO(max(x_i)^2)
*/

const int MAX_Xi = 2017;

int N, L;
int ma_x;
int S[MAX_Xi];
bool dp[MAX_Xi];
bool visited[MAX_Xi];

// (l, r)
bool empty(int l, int r) {
    l++;
    if (l >= r) return true;
    return S[l] - S[r] == 0;
}

bool f(int i) {
    if (i > ma_x) return true;
    if (visited[i]) return dp[i];
    visited[i] = true;
    for (int j = i; j <= ma_x; ++j) {
        // cerr << i << " " << j << " " << empty(i - 1, j) << " " << empty(j + L, j + 2 * L) << " " << endl;
        // ジャンプしないとき
        dp[i] |= (empty(i - 1, j) && f(j));
        // ジャンプするとき
        dp[i] |= (empty(i - 1, j) && empty(j + L, j + 2 * L) && f(j + 2 * L));
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

    // rep(i, 2 * ma_x) {
    //     cerr << S[i] << " ";
    // }
    // cerr << endl;
    //
    cout << (f(0) ? "YES" : "NO") << endl;
    //
    // rep(i, 2 * ma_x) {
    //     cerr << dp[i] << " ";
    // }
    // cerr << endl;
    // rep(i, 2 * ma_x) {
    //     cerr << visited[i] << " ";
    // }
    // cerr << endl;

    // rep(i, 2 * ma_x) {
    //     rep(j, 2 * ma_x) {
    //         cerr << i << " " << j << " " << empty(i, j) << endl;
    //     }
    // }
}
