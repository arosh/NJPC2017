#include <iostream>
using namespace std;

#define rep(i,n) for (int i=0;i<(n);i++)
#define rep2(i,a,b) for (int i=(a);i<(b);i++)

const int inf = 1<<30;
const int MAX_N = 1001;
bool dp[MAX_N][MAX_N]; // dp[l, r) = S[l, r)を構築可能か？
bool visited[MAX_N][MAX_N];
int order[MAX_N][MAX_N]; // order[l][k] = S[l, k)<=S[k, r)なる最小のr
string s;

bool f(int l, int r) {
    if (l >= r - 1) return true; // 1文字以下
    if (visited[l][r]) return dp[l][r];
    visited[l][r] = true;
    for (int k = l + 1; k <= r; ++k) {
        if (f(l, k) && f(k, r) && order[l][k] <= r) {
            return dp[l][r] = true;
        }
    }
    return false;
}

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    cin >> s;
    int n = s.size();

    rep(l, n) {
        rep2(k, l + 1, n) {
            order[l][k] = inf;
            rep2(r, k + 1, n + 1) {
                if (s[l + r - 1 - k] > s[r - 1]) {
                    break;
                }
                if (s[l + r - 1 - k] < s[r - 1] || r - k == k - l) {
                    order[l][k] = r;
                    break;
                }
            }
        }
    }

    // rep(l, n) {
    //     rep2(k, l + 1, n + 1) {
    //         cerr << l << ", " << k << ", " << order[l][k] << endl;
    //     }
    // }

    cout << (f(0, s.size()) ? "Yes" : "No") << endl;
}
