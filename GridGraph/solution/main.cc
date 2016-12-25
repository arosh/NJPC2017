#include <iostream>
#include <vector>
using namespace std;

#define rep(i,n) for (int i=0;i<(n);i++)
#define rep2(i,a,b) for (int i=(a);i<(b);i++)
#define rrep(i,n) for (int i=(n)-1;i>=0;i--)
#define rrep2(i,a,b) for (int i=(b)-1;i>=(a);i--)
#define all(a) (a).begin(),(a).end()

typedef long long ll;
typedef pair<int, int> P;
typedef vector<int> vi;
typedef vector<P> vp;
typedef vector<ll> vll;

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    ll H, W;    // ansの計算に使うのでllに！！！
    int N;
    cin >> H >> W >> N;

    // 'x'の座標
    vector<int> x(N);
    vector<int> y(N);
    rep(i, N) {
        int xx, yy;
        cin >> xx >> yy;
        x[i] = xx;
        y[i] = yy;
    }

    // すべて 'o' と仮定したときの辺の本数
    ll ans = H * (W - 1) + W * (H - 1);

    // 'x'に隣接する辺を除く
    rep(i, N) {
        // 'x'に隣接する辺をまず4本と仮定する
        ll dame = 4;
        // 端だったら 1 本除く (上下左右それぞれについて調べる)
        if (x[i] == 1) dame--;
        if (x[i] == H) dame--;
        if (y[i] == 1) dame--;
        if (y[i] == W) dame--;

        ans -= dame;
    }

    // 隣接する　'x' の間の辺は 2 回除いてしまったので、 1 回足す
    rep(j, N) {
        rep(i, j) {
            if ((x[i] == x[j] && abs(y[i] - y[j]) == 1) || (abs(x[i] - x[j]) == 1 && y[i] == y[j])) {
                ans++;
            }
        }
    }

    cout << ans << endl;

}
