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

int main(){
    int n,l;
    cin>>n>>l;
    vector<int> x(n);
    rep(i,n)cin>>x[i];
    
    vector<pii> seg;
    
    int left=-1,right=-1;
    for(auto t:x){
        if(left==-1){
            left = t;
            right = t;
        }
        else if(t-right<=l){
            right = t;
        }
        else{
            seg.pb(pii(left,right));
            left=t;
            right=t;
        }
    }
    if(left!=-1||right!=-1)seg.pb(pii(left,right));
    
    
    rep(i,seg.size()){
        if(seg[i].second - seg[i].first>=l){
            cout<<"NO"<<endl;
            return 0;
        }
    }
    rep(i,seg.size()-1){
        if(seg[i+1].first - seg[i].second - 2<l){
            cout<<"NO"<<endl;
            return 0;
        }
    }
    if(seg[seg.size()-1].second<l){
        cout<<"YES"<<endl;
        return 0;
    }
    if(seg[0].second-l-1<0){
        cout<<"NO"<<endl;
        return 0;
    }
    cout<<"YES"<<endl;
}
