#include<iostream>
#include<vector>
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
    for(int i=1;i<=n;i++){
        int dt = t[i]-t[i-1];
        if(abs(x[i]-x[i-1])<=dt*v+EPS){
            left -= dt*v;
            right+= dt*v;
        }else if(left-dt*v<=x[i]+EPS && x[i]-EPS<=right+dt*v){
            left = x[i-1]-dt*v;
            right= x[i-1]+dt*v;
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