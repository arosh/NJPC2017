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

// これは嘘

bool update(vector<int>& a) {
	// 先頭が0でなければダメ
	if (a[0] != 0) return false;
	int n = a.size();
	map<vector<int>, int> mp;
	vector<vector<int>> vv;
	vector<int> v;

	// "00" -> -1, "000" -> -2, ...とする
	rep(i, n) {
		if (i != 0 && a[i - 1] == 0 && a[i] == 0) {
			v[0]--;
		} else {
			if (v.size() > 1 && a[i] == 0) {
				mp[v] = 0;
				vv.emplace_back(v);
				v.clear();
			}
			v.emplace_back(a[i]);
		}
	}
	mp[v] = 0;
	vv.emplace_back(v);

	{
		int i = 0;
		for (auto& p : mp) {
			p.second = i++;
		}
	}

	vector<int> b;
	for (auto u : vv) {
		b.emplace_back(mp[u]);
	}

	bool ret = (a != b);
	a = b;
	return ret;
}

// 連続する0を潰す解法
// (文字を辞書順に0, 1, 2, ...に変換して考える)
// a = {0}となったら終了
signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

	string s;
	while (cin >> s) {
		map<char, int> mp;
		for (auto c : s) mp[c] = 0;
		{
			int i = 0;
			for (auto& p : mp) {
				p.second = i++;
			}
		}
		int n = s.size();
		vector<int> a(n);
		rep(i, n) {
			a[i] = mp[s[i]];
		}

		// printV(a);

		while (update(a)) {
			;
		}

		cout << (a == vector<int>{0} ? "Yes" : "No") << endl;
	}
}
