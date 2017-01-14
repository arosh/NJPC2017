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

struct edge {
    int to, id;
    edge(){}
    edge(int _to, int _id) : to(_to), id(_id) {}
};
using Graph = vector<vector<edge>>;

Graph G;
vi v_begin;
vi e_plus;
vi e_minus;
vi e_cost;

class Bit {
private:
    vector<int> bit;
    const int n;

public:
    Bit(int _n) : n(_n), bit(_n + 1) {}

    // get sum in [1, i]
    // sum{[i, j]} = sum{[1, j]} - sum{[1, i-1]}
    int sum(int i) {
        int s = 0;
        while (i > 0) {
            s += bit[i];
            i -= i & -i;
        }
        return s;
    }

    // [l, r]
    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    // add x to bit[i]
    void add(int i, int x) {
        while (i <= n) {
            bit[i] += x;
            i += i & -i;
        }
    }

    void print() {
        rep2(i, 1, n) {
            cerr << (i ? " " : "") << sum(i, i);
        }
        cerr << endl;
    }
};


class LCA {
private:
    static const int MAX_LOG = 20;
    const int n;
    vector<vector<int>> par;
    vector<int> depth;

    // 各頂点の深さと、1つ前の親を求める
    void dfs(int v, int p, int d) {
        par[0][v] = p;
        depth[v] = d;
        for (auto e : G[v]) {
            if (e.to != p) {
                dfs(e.to, v, d + 1);
            }
        }
    }
public:
    LCA(int _n) : n(_n), par(MAX_LOG, vector<int>(_n)), depth(_n) {}
    // 各頂点の2^k番目の親を求めておく
    void init() {
        // 0を根として1つ目の親を求める
        dfs(0, -1, 0);

        // 2^i番目の親を求める
        rep(i, MAX_LOG - 1) {
            rep(j, n) {
                if (par[i][j] == -1) {
                    par[i + 1][j] = -1;
                } else {
                    par[i + 1][j] = par[i][par[i][j]];
                }
            }
        }
    }
    int lca(int a, int b) {
        // まずaとbの深さを揃える
        if (depth[a] > depth[b]) {
            swap(a, b);
        }
        rep(i, MAX_LOG) {
            if ((depth[b] - depth[a]) >> i & 1) {
                b = par[i][b];
            }
        }
        if (a == b) return a;

        // ぶつかる直前までa, bを上げる
        rrep(i, MAX_LOG) {
            if (par[i][a] != par[i][b]) {
                a = par[i][a];
                b = par[i][b];
            }
        }
        // aとbの1つ前の親は一致している
        return par[0][a];
    }
};


void dfs(int now, int pre, int& i) {
    // output(now, pre, i);
    if (v_begin[now] == -1) v_begin[now] = i;
    for (auto e : G[now]) {
        // output(e.to, e.id);
        if (e.to == pre) continue;
        e_plus[e.id] = i++;
        dfs(e.to, now, i);
        e_minus[e.id] = i++;
    }
}

void printGraph(const Graph& G) {
    rep(i, G.size()) {
        cout << i << ": ";
        rep(j, G[i].size()) {
            cout << "{" << G[i][j].to << ", " << G[i][j].id << "}, ";
        }
        cout << endl;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int N;
    cin >> N;
    G.resize(N);
    vi p(N, -1);
    rep2(i, 1, N) {
        cin >> p[i];
        p[i]--;
        G[p[i]].emplace_back(i, i - 1);
    }

    vi C(N);
    rep(i, N) cin >> C[i];
    e_cost.resize(N - 1);
    rep2(i, 1, N) {
        if (C[i] == C[p[i]]) {
            // output(i, p[i], C[i], C[p[i]]);
            e_cost[i - 1] = 1;
        }
    }

    v_begin.resize(N, -1);
    e_plus.resize(N - 1, -1);
    e_minus.resize(N - 1, -1);

    int id = 1;
    dfs(0, -1, id);

    // printGraph(G);
    // printV(v_begin);
    // printV(e_plus);
    // printV(e_minus);
    // printV(e_cost);

    Bit bit(id);
    rep(i, N - 1) {
        bit.add(e_plus[i], e_cost[i]);
        bit.add(e_minus[i], -1 * e_cost[i]);
    }

    // bit.print();

    LCA lca(N);
    lca.init();

    int Q;
    cin >> Q;
    rep(i, Q) {
        // output("query", i + 1, ":");
        int t;
        cin >> t;
        if (t == 1) {
            int u;
            cin >> u;
            // output(t, u);
            u--;
            if (u != 0) {
                if (e_cost[u - 1] == 1) {
                    bit.add(e_plus[u - 1], -1);
                    bit.add(e_minus[u - 1], +1);
                }
                else {
                    bit.add(e_plus[u - 1], +1);
                    bit.add(e_minus[u - 1], -1);
                }
                e_cost[u - 1] ^= 1;
            }
        }
        else {
            int u, v;
            cin >> u >> v;
            // output(t, u, v);
            u--; v--;
            int x = lca.lca(u, v);
            int t = bit.sum(v_begin[x], v_begin[u] - 1) + bit.sum(v_begin[x], v_begin[v] - 1);
            // output(u, v, x);
            // output(bit.sum(v_begin[x], v_begin[u] - 1));
            // output(bit.sum(v_begin[x], v_begin[v] - 1));
            cout << (t == 0 ? "YES" : "NO") << endl;
        }
        // bit.print();
    }
}
