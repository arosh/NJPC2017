#include <iostream>
#include <vector>
using namespace std;

#define rep(i,n) for (int i=0;i<(n);i++)
#define rep2(i,a,b) for (int i=(a);i<(b);i++)
#define rrep(i,n) for (int i=(n)-1;i>=0;i--)
#define rrep2(i,a,b) for (int i=(a)-1;i>=b;i--)
#define all(a) (a).begin(),(a).end()
#define rall(a) (a).rbegin(),(a).rend()

// AC: 1つめのifとelse ifが逆だけど関係ない

int main() {
    int N, L;
    cin >> N >> L;
    vector<int> x(N);
    rep(i, N) cin >> x[i];

    int i = 0;
    int p = 0;
    int l = x[0];
    for(; i < N - 1; i++) {
        if (x[i + 1] - l < L) {
            continue;
        }
        else if (x[i + 1] > max(x[i] + L, p + 2 * L)) {
            p = max(x[i] + L, p + 2 * L);
            l = x[i + 1];
        }
        else {
            break;
        }
    }

    cout << (i == N - 1 ? "YES" : "NO") << endl;
}
