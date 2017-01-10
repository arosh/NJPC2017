#include<iostream>
#include<vector>
using namespace std;
typedef long long ll;
#define rep(i,n) for(ll i=0;i<(ll)(n);i++)
#define pb push_back

vector<int> conv(vector<int> v,int &k){
	if(k==0)return v;
	
	int p = 0;
	while(1){
		int dec = v.size()-p-1;
		if(k>=dec){
			int val = v[0];
			v.insert(v.end()-p,val);
			v.erase(v.begin());
			p++;
			k-=dec;
		}
		else{
			int val = v[0];
			v.erase(v.begin());
			v.insert(v.begin()+k,val);
			k=0;
		}
		if(v.size()-p-1==0 || k==0)break;
	}
	return v;
}


int main(){
	int h,w,k;
	cin>>h>>w>>k;
	
	bool swapped = false;
	if(h>w){
		swapped = true;
		swap(h,w);
	}
	
	
	vector<vector<int>> ans(h,vector<int>(w));
	if(k<=h*w*(w-1)/2){
		rep(i,h) rep(j,w) ans[i][j] = i*w+j;
	}
	else{
		k = (h*w*(w-1)/2 + w*h*(h-1)/2-k);
		rep(i,h) rep(j,w) ans[i][j] = (h-i-1)*w+(w-j-1);
	}
	
	rep(i,h) ans[i] = conv(ans[i],k);
	
	
	vector<vector<int>> res(h,vector<int>(w));
	if(swapped){
		rep(j,w){
			rep(i,h){
				if(i)cout<<" ";
				cout<<ans[i][j]+1;
			}
			cout<<endl;
		}
		
	}
	else{
		rep(i,h){
			rep(j,w){
				if(j)cout<<" ";
				cout<<ans[i][j]+1;
			}
			cout<<endl;
		}
	}
}