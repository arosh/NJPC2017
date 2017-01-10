#include<iostream>
#include<vector>
#include<set>

using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define rep(i,n) for(ll i=0;i<(ll)(n);i++)

int main(){
    int h,w,n;
    cin>>h>>w>>n;
    
    vector<pii> p(n);
    rep(i,n){
        int a,b;
        cin>>a>>b;
        p[i]=pii(a-1,b-1);
    }
    
    int dy[]={1,0,-1,0};
    int dx[]={0,1,0,-1};

    set<pii> st;
    ll overlap = 0;
    ll edge = 0;
    rep(i,p.size()){
        int y,x;
        tie(y,x) = p[i];
        rep(j,4){
            int ddy = y+dy[j];
            int ddx = x+dx[j];
            if(ddy<0||ddx<0||ddy>=h||ddx>=w)edge++;
            else if(st.count(pii(ddy,ddx))!=0)overlap++;
        }
        st.insert(p[i]);
    }
    
    ll sum = ( (ll)h*w*4 - 2*(h+w) )/2;
    cout<<sum - n*4 + edge + overlap<<endl;
}