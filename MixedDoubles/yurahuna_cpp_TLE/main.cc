#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

#define rep(i,n) for (int i=0;i<(n);i++)
#define rep2(i,a,b) for (int i=(a);i<(b);i++)
#define rrep(i,n) for (int i=(n)-1;i>=0;i--)
#define rrep2(i,a,b) for (int i=(b)-1;i>=(a);i--)
#define all(a) (a).begin(),(a).end()

typedef long long ll;
typedef pair<int, int> P;

// O(N^2) DP
// dp配列は2行だけとって使いまわす
const int MAX_N = 100001;
const double INF = 1e10;

int N;
double T[MAX_N], X[MAX_N];

// dp[i][j] = i番目のボールを打ち返したとき、もう1人が最後に打ち返したボールがjであるような場合に、それまでに出した最大の速度の最小値
double dp1[MAX_N];
double dp2[MAX_N];

int main() {
    scanf("%d\n", &N);
    rep2(i, 1, N + 1) {
        scanf("%lf %lf\n", &T[i], &X[i]);
    }

    fill(dp1, dp1 + MAX_N, INF);
    dp1[0] = fabs(X[1]) / T[1];
    // rep(k, N + 1) {
    //     printf("%.5f ", dp1[k]);
    // }
    // printf("\n");

    rep2(i, 1, N) {
        fill(dp2, dp2 + MAX_N, INF);
        rep(j, i) {
            // iがi+1を打ちに行く場合 -> もう1人はjにいる
            dp2[j] = min(dp2[j], max(dp1[j], fabs(X[i + 1] - X[i]) / (T[i + 1] - T[i])));
            // jがi+1を打ちに行く場合 -> もう1人はiにいる
            dp2[i] = min(dp2[i], max(dp1[j], fabs(X[i + 1] - X[j]) / (T[i + 1] - T[j])));
        }
        swap(dp1, dp2);

        // rep(k, N + 1) {
        //     printf("%.5f ", dp1[k]);
        // }
        // printf("\n");
    }

    double ans = *min_element(dp1, dp1 + MAX_N);
    printf("%.10f\n", ans);

}
