#include <bits/stdc++.h>
using namespace std;

#define rep(i,n) for (int i=0;i<(n);i++)
#define rep2(i,a,b) for (int i=(a);i<(b);i++)
#define rrep(i,n) for (int i=(n)-1;i>=0;i--)
#define rrep2(i,a,b) for (int i=(a)-1;i>=b;i--)
#define chmin(a,b) (a)=min((a),(b));
#define chmax(a,b) (a)=max((a),(b));
#define all(a) (a).begin(),(a).end()
#define rall(a) (a).rbegin(),(a).rend()
#define printV(v) cout<<(#v)<<":";for(auto(x):(v)){cout<<" "<<(x);}cout<<endl;
#define printVS(vs) cout<<(#vs)<<":"<<endl;for(auto(s):(vs)){cout<<(s)<< endl;}
#define printVV(vv) cout<<(#vv)<<":"<<endl;for(auto(v):(vv)){for(auto(x):(v)){cout<<" "<<(x);}cout<<endl;}
#define printP(p) cout<<(#p)<<(p).first<<" "<<(p).second<<endl;
#define printVP(vp) cout<<(#vp)<<":"<<endl;for(auto(p):(vp)){cout<<(p).first<<" "<<(p).second<<endl;}

inline void output(){ cout << endl; }
template<typename First, typename... Rest>
inline void output(const First& first, const Rest&... rest) {
    cout << first << " "; output(rest...);
}

using ll = long long;
using Pii = pair<int, int>;
using TUPLE = tuple<int, int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;
const int inf = 1e9;
const int mod = 1e9 + 7;

struct edge {
    int to, cost, reversed;
    edge(){}
    edge(int _to, int _cost, int _reversed) : to(_to), cost(_cost), reversed(_reversed) {}
};
using Graph = vector<vector<edge>>;

Graph G;
vector<int> cnt;

// a -> b
void addEdge(int a, int b, int c) {
    G[a].emplace_back(b, c, 0);
    G[b].emplace_back(a, c, 1);
}

// 距離を求める用
void dfs(int now, int pre, vector<int>& d) {
    if (pre == -1) d[now] = 0;
    for (auto e : G[now]) {
        if (e.to == pre) continue;
        d[e.to] = d[now] + e.cost;
        dfs(e.to, now, d);
    }
}

// 頂点0への反転回数を求める用
int dfs2(int now, int pre) {
    int ret = 0;
    for (auto e : G[now]) {
        if (e.to == pre) continue;
        ret += e.reversed ^ 1;
        ret += dfs2(e.to, now);
    }
    return ret;
}

// 各頂点への反転回数を求める用
void dfs3(int now, int pre) {
    for (auto e : G[now]) {
        if (e.to == pre) continue;
        cnt[e.to] = cnt[now] + (e.reversed ? +1 : -1);
        dfs3(e.to, now);
    }
}

main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int N, D;
    cin >> N >> D;
    G.resize(N);
    rep(i, N - 1) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        addEdge(a, b, c);
    }

    vector<int> d0(N), d1(N), d2(N);
    dfs(0, -1, d0);
    // v1, v2: 直径の両端
    int v1 = max_element(all(d0)) - d0.begin();
    dfs(v1, -1, d1);
    int v2 = max_element(all(d1)) - d1.begin();
    dfs(v2, -1, d2);

    cnt.resize(N);
    // 頂点0にすべての辺を向けるために必要な反転回数を求める
    cnt[0] = dfs2(0, -1);

    // cnt[0]を利用し、cnt[i](i=1..N-1)を求める
    dfs3(0, -1);

    int ans = inf;
    rep(i, N) {
        if (max(d1[i], d2[i]) <= D) {
            ans = min(ans, cnt[i]);
        }
    }

    // output(v1, v2);
    // printV(d1);
    // printV(d2);
    // printV(cnt);

    cout << (ans == inf ? -1 : ans) << endl;
}
