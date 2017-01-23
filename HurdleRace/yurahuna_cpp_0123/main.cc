#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define rep(i,n) for (int i=0;i<(n);i++)
#define rep2(i,a,b) for (int i=(a);i<(b);i++)

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int N, L;
    cin >> N >> L;
    vector<int> x(N);
    rep(i, N) cin >> x[i];

    auto ret = [&](){
        int p = 0;
        int l = x[0];
        rep(i, N - 1) {
            if (x[i + 1] - x[i] == L) {
                return false;
            }
            else if (x[i + 1] - x[i] > L) {
                if (x[i + 1] > p + 2 * L) {
                    p = max(p + 2 * L, x[i] + L);
                    l = x[i + 1];
                }
                else {
                    return false;
                }
            }
            else {
                if (x[i + 1] - l >= L) {
                    return false;
                }
            }
        }
        return true;
    }();

    cout << (ret ? "YES" : "NO") << endl;

}
