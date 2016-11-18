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

void output(const vector<vector<int>>& a, bool flag_rev) {
	int N = a.size();
	int M = a[0].size();
	if (flag_rev) {
		rep(j, M) {
			rep(i, N) {
				cout << a[i][j] << (i != N - 1 ? " " : "");
			}
			cout << endl;
		}
	} else {
		rep(i, N) {
			rep(j, M) {
				cout << a[i][j] << (j != M - 1 ? " " : "");
			}
			cout << endl;
		}
	}
}

// 想定解法
signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

	int N, M, K;
	cin >> N >> M >> K;

	bool flag_rev = false;
	if (N > M) {
		flag_rev = true;
		swap(N, M);
	}
	// N <= M

	vector<vector<int>> a(N, vector<int>(M));
	{
		// 最小ケースから
		int t = 1;
		rep(i, N) rep(j, M) a[i][j] = t++;
		int cnt = 0;
		if (cnt == K) {
			output(a, flag_rev);
			return 0;
		}
		rep(i, N) {
			for (int k = M - 1; k >= 1; k--) {
				rep(j, k) {
					swap(a[i][j], a[i][j + 1]);
					cnt++;
					if (cnt == K) {
						output(a, flag_rev);
						return 0;
					}
				}
			}
		}
	}
	{
		// 最大ケースから
		int t = N * M;
		rep(i, N) rep(j, M) a[i][j] = t--;
		int cnt = N * M * (M - 1) / 2;
		if (cnt == K) {
			output(a, flag_rev);
			return 0;
		}
		rep(i, N) {
			for (int k = M - 1; k >= 1; k--) {
				rep(j, k) {
					swap(a[i][j], a[i][j + 1]);
					cnt--;
					if (cnt == K) {
						output(a, flag_rev);
						return 0;
					}
				}
			}
		}
	}

	// 不可能なケースも入れるなら
	// cout << -1 << endl;
}
