#include <bits/stdc++.h>
using namespace std;

#define rep(i,n) for (int i=0;i<(n);i++)
#define rep2(i,a,b) for (int i=(a);i<(b);i++)
#define rrep(i,n) for (int i=(n)-1;i>=0;i--)
#define rrep2(i,a,b) for (int i=(a)-1;i>=b;i--)
#define all(a) (a).begin(),(a).end()
#define rall(a) (a).rbegin(),(a).rend()

// デバッグ用
#define printV(_v) for(auto _x:_v){cout<<_x<<" ";}cout<<endl
#define printVS(_vs) for(auto _x : _vs){cout << _x << endl;}
#define printVV(_vv) for(auto _v:_vv){for(auto _x:_v){cout<<_x<<" ";}cout<<endl;}
#define printP(_p) cout << _p.first << " " << _p.second << endl
#define printVP(_vp) for(auto _p : _vp) printP(_p);

typedef long long ll;
const int mod = 1e9 + 7;

// 部分点ケースに対する解法(青い台だけのとき)
// 一点加算のみのDP
// 状態数O(HW), 遷移O(1)→全体でO(HW)
// ここまでなら幸せなんだけどなあ・・・。
signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int H, W, s, A, B;
    cin >> H >> W >> s >> A >> B;
    int N;
    cin >> N;
    // blue[i] = i段目(y==i+1)の青い台を左から順に並べたもの
    vector<vector<pair<int,int>>> blue(H - 1);
    rep(i, N) {
        int l, r, y;
        cin >> l >> r >> y;
        blue[y - 1].emplace_back(l, r);
    }

    // rep(i, H - 1) {
    //     cerr << i << ":" << endl;
    //     printVP(blue[i]);
    // }

    int M;
    cin >> M;
    vector<vector<pair<int,int>>> red(H - 1);
    rep(i, M) {
        int l, r, y;
        cin >> l >> r >> y;
        red[y - 1].emplace_back(l, r);
    }

    // dp[i][j] = マス(i+1,j)に至る経路の数
    vector<vector<int>> dp(H, vector<int>(W));
    dp[0][s] = 1;
    rep(i, H - 1) {
        int k = -1; // この段で直前に通り過ぎた青い台が左から何番目か
        bool on_segment = false;
        int l = -1, r = -1;
        rep(j, W) {
            if (k + 1 < (int)blue[i].size() && j >= blue[i][k + 1].first) {
                on_segment = true;
                k++;
                tie(l, r) = blue[i][k];
            } else if (r <= j) {
                on_segment = false;
                l = -1; r = -1;
            }
            // cerr << i << " " << j << " " << k << " " << l << " " << r << endl;

            if (!on_segment) {
                // 法則2に従うとき
                (dp[i + 1][j] += dp[i][j]) %= mod;
            } else {
                // 指示'L'
                if (l - 1 >= 0) {
                    (dp[i + 1][l - 1] += dp[i][j]) %= mod;
                }
                // 指示'R'
                if (r < W) {
                    (dp[i + 1][r] += dp[i][j]) %= mod;
                }
            }
        }
    }

    int ans = 0;
    rep2(j, A, B + 1) {
        (ans += dp[H - 1][j]) %= mod;
    }

    // printVV(dp);

    cout << ans << endl;
}
