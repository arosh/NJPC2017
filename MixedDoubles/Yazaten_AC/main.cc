#include <cstdio>
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define rep(i,n) for(ll i=0;i<(ll)(n);i++)
#define all(a)  (a).begin(),(a).end()
#define pb push_back
#define INF (1e9+1)
//#define INF (1LL<<59)
#define int ll
#define EPS 1e-9

int n;
vector<int> t,x;
bool solve(double v){
	double left=0,right=0;
	for(int i=0;i<n;i++){
		double w = v * (t[i+1]-t[i]);

		bool seg=left-w<=x[i+1]+EPS && x[i+1]-EPS<=right+w;	//x[i]を打たなかった人(区間)が拾えるか
		bool bef=abs(x[i+1]-x[i])<=w+EPS;			//x[i]を打った人が拾えるか
		if(i==0)seg=false;

		if( seg && !bef ){		//区間の人しか拾えない
			left  = x[i]-w;
			right = x[i]+w;
		}else if( !seg && bef ){	//x[i]の人しか拾えない
			left -= w;
			right+= w;
		}else if( seg && bef ){		//両者が拾える場合
			double hl = x[i]-w, hr = x[i]+w;
			double sl = left-w,	  sr = right+w;
			assert( (hl<=sl && sl<=hr) || (sl<=hl && hl<=sr) );
			//x[i]の人が取った時の区間と、区間が取ったときの区間は必ず交差する

			left = min(hl,sl);
			right= max(hr,sr);
		}else{
			return false;
		}
	}
	return true;
}

signed main(){
	cin>>n;

	t.resize(n+1,0);
	x.resize(n+1,0);
	for(int i=1;i<=n;i++)cin>>t[i]>>x[i];

	double left=0, right=1e7, mid=(left+right)/2LL;
	rep(loop,100){
		bool res = solve(mid);

		if(!res) left = mid;
		else    right= mid;

		mid = (left+right)/2LL;
	}

	printf("%.20lf\n",mid);

}
