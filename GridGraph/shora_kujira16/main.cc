#include <bits/stdc++.h>
using namespace std;
#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define DEBUG(x) cerr << #x << " = " << x << endl
#define int long long
typedef pair<int, int> P;
int dx[] = {1, 0, -1, 0};
int dy[] = {0, -1, 0, 1};
signed main() {
  int H, W; cin >> H >> W;
  int N; cin >> N;
  vector<P> ps(N);
  REP(i,N) {
    cin >> ps[i].first >> ps[i].second;
  }
  int x = (W - 1) * H + (H - 1) * W;
  int sub = 0;
  int add = 0;
  REP(i,N) {
    REP(k,4) {
      int ny = ps[i].first + dy[k];
      int nx = ps[i].second + dx[k];
      if(1 <= ny && ny <= H && 1 <= nx && nx <= W) {
        sub++;
      }
    }
    REP(j,N) {
      if(abs(ps[i].first - ps[j].first) + abs(ps[i].second - ps[j].second) == 1) {
        add++;
      }
    }
  }
  cout << x - sub + add / 2 << endl;
}
