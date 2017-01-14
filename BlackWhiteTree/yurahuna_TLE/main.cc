#include <iostream>
#include <algorithm>
#include <vector>
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
using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;
const int inf = 2e9;
const int mod = 1e9 + 7;
using Graph = vector<vector<int>>;

Graph G;
vi p;
vi C;

void changeColor(int now) {
    C[now] ^= 1;
    for (auto nxt : G[now]) {
        if (nxt == p[now]) continue;
        changeColor(nxt);
    }
}

bool reachable(int now, int pre, int g) {
    if (now == g) return true;
    bool ret = false;
    for (auto nxt : G[now]) {
        if (nxt == pre) continue;
        if (C[nxt] != C[now]) {
            ret |= reachable(nxt, now, g);
        }
    }
    return ret;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int N;
    cin >> N;
    G.resize(N);
    p.resize(N, -1);
    rep2(i, 1, N) {
        cin >> p[i];
        p[i]--;
        G[p[i]].emplace_back(i);
        G[i].emplace_back(p[i]);
    }

    C.resize(N);
    rep(i, N) cin >> C[i];

    int Q;
    cin >> Q;
    rep(i, Q) {
        int t;
        cin >> t;
        if (t == 1) {
            int u;
            cin >> u;
            u--;
            changeColor(u);
        }
        else {
            int u, v;
            cin >> u >> v;
            u--; v--;
            cout << (reachable(u, -1, v) ? "YES" : "NO") << endl;
        }
    }
}