#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define rep(i,n) for (int i=0;i<(n);i++)
#define rep2(i,a,b) for (int i=(a);i<(b);i++)
#define rrep(i,n) for (int i=(n)-1;i>=0;i--)
#define rrep2(i,a,b) for (int i=(b)-1;i>=(a);i--)
#define all(a) (a).begin(),(a).end()

typedef long long ll;
typedef pair<int, int> P;

const int MAX_N = 100001;
const double INF = 1e10;

int N;
double T[MAX_N], X[MAX_N];

// 速さの上限vですべてのボールを打ち返せるか？
bool check(double v) {
    // i番目のボールを打ち返したとき、もう1人が存在可能な区間: [l ,r]
    // 最初は原点のみ
    double l = 0, r = 0;

    rep(i, N) {
        double nl = INF, nr = -INF;

        // iからi+1までの時間に区間が広がる幅
        double w = v * (T[i + 1] - T[i]);

        // iがi+1に到達可能ならば、もう1人は自由に動ける
        if (X[i] - w <= X[i + 1] && X[i + 1] <= X[i] + w) {
            nl = min(nl, l - w), nr = max(nr, r + w);
        }

        // iを打たなかった方がi+1に到達可能ならば、iを打った方は自由に動ける
        if (l - w <= X[i + 1] && X[i + 1] <= r + w) {
            nl = min(nl, X[i] - w), nr = max(nr, X[i] + w);
        }

        // i+1に到達不可能ならfalse
        if (nl > nr) {
            return false;
        }

        l = nl;
        r = nr;
    }

    return true;
}

int main() {
    scanf("%d\n", &N);
    rep2(i, 1, N + 1) scanf("%lf %lf\n", &T[i], &X[i]);

    double l = 0;
    double r = INF;
    rep(i, 100) {
        double m = (l + r) / 2;
        if (check(m)) {
            r = m;
        } else {
            l = m;
        }
    }

    // 誤差を出してみる
    printf("%.10f\n", r + 1);

}
