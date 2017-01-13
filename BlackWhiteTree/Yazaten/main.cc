#include<iostream>
#include<vector>

using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define rep(i,n) for(ll i=0;i<(ll)(n);i++)
#define all(a)  (a).begin(),(a).end()
#define pb push_back
#define INF (1e9+1)

#define MAX_V 150000
struct edge{ int to,cost; };
vector<edge> G[MAX_V];


//LCA(セグ木版)----------------------------------------------------------------------------------------
vector<int> depth,vs;
int id[MAX_V]={};

template<class T>
class segtree{
private:
	vector<T> dat;
	int _size;  //the number of leaves
	T _init;
	
public:
	segtree(int __size=0 , T init=numeric_limits<T>::max() ):_size(__size) , _init(init) , dat(4*__size,init){
		if(__size==0)return ;
		int x=1;
		while(x<_size)x*=2;
		_size = x;
	}
	
	void update(int m,T x){
		int i = m+_size;
		//      dat[i] += x;   If uou want addition when update.
		dat[i] = x;
		while(i!=1){
			dat[i/2] = min(dat[i],dat[i^1]);
			i/=2;
		}
	}
	
	// call find(s,t)
	T find(int s,int t,int num=1,int a=0,int b=-1){
		if(b==-1)b=_size-1; //I couldn't "int b=_size".
		if(b<s||t<a)return _init;
		if(s<=a&&b<=t)return dat[num];
		return min( find(s,t,num*2,a,(a+b)/2) , find(s,t,num*2+1,(a+b)/2+1,b) );
	}
	int size(){return _size;}
};


void lcaTour(int d,int prev,int num){    //オイラーツアー depth(深さ),vs(ノード番号)
	depth.pb(d);
	vs.pb(num);
	rep(i,G[num].size()){
		if(G[num][i].to==prev)continue;
		lcaTour(d+1,num,G[num][i].to);
		depth.pb(d);
		vs.pb(num);
	}
	return ;
}


void init(){
	lcaTour(1,-1,0);
	rep(i,vs.size()){
		if(id[ vs[i] ]==0)id[ vs[i] ]=i;
	}
}


pii LCA (int a,int b,segtree<pii> &st){ //最小共通祖先の深さを返す
	int arg1 = id[a];
	int arg2 = id[b];
	if(arg1>arg2)swap(arg1,arg2);
	return st.find(arg1,arg2);
}

//---------------------------------------------------------------------------------------------------


//EulerTourとBIT-------------------------------------------------------------------------------------
vector<int> et, begv(MAX_V), endv(MAX_V);
void tour(int cur,int prev){
	begv[cur] = et.size();
	et.pb(cur);
	for(auto e:G[cur]){
		if(e.to==prev)continue;
		tour(e.to,cur);
		et.pb(cur);
	}
	endv[cur]=et.size();
}


//verified
//note that this is 1-index
template<class T>
class BIT{
private:
	vector<T> sum_of_section_;
	int elements_count_;
	T init_;
	
public:
	BIT(int elements_count=0 , T init=0):elements_count_(elements_count*2),init_(init),sum_of_section_(elements_count*2+1,0){
		for(int i=0;i<elements_count_;i++) add(i+1,init);
	}
	
	T sum(int i){   //(1,i)
		int sum=0;
		while(i>0){
			sum+=sum_of_section_[i];
			i -= i&-i;
		}
		return sum;
	}
	
	void add(int i,T val){
		while(i<=elements_count_){
			sum_of_section_[i]+=val;
			i += i&-i;
		}
	}
	
	T get_cost(int u,int v,segtree<pii> &st){
		int lca=LCA(u,v,st).second;
		return ( sum(begv[u]+1)-sum(begv[lca]+1) + sum(begv[v]+1)-sum(begv[lca]+1) );
	}
	
	void rev_cost(int u,int v,segtree<pii> &st){
		//u は v の親である
		int res = get_cost(u,v,st);
		if( res==0 ){
			add(begv[v]+1,+1);
			add(endv[v],-1);
		}else{
			add(begv[v]+1,-1);
			add(endv[v],+1);
		}
	}
};

//---------------------------------------------------------------------------------------------------


//以下が実質的な実装部分---------------------------------------------------------------------------------
void dfs(int cur,int prev, BIT<int> &bt, vector<int> &c, segtree<pii> &st){
	for(auto e:G[cur]){
		if(e.to==prev)continue;
		if(c[cur]==c[e.to])bt.rev_cost(cur, e.to,st);
		dfs(e.to,cur,bt,c,st);
	}
}


int main(){
	int v;
	cin>>v;

	vector<int> par(v);
	for(int i=1;i<v;i++){
		int p;
		cin>>p;
		p--;
		par[i]=p;
		G[i].pb(edge{p,0});
		G[p].pb(edge{i,0});
	}

	//LCA用にオイラーツアー + セグ木
	init();                                                         // aranging depth[] , vs[] and id[]
	segtree<pii> st(depth.size(),pii((1LL<<31)-1,(1LL<<31)-1));     // the number of elements is depth.size()
	rep(i,depth.size()){                                            //initialize
		st.update(i,pii(depth[i],vs[i]));
	}
	
	//パス間の距離用にオイラーツアー + BIT
	tour(0,-1);
	BIT<int> bt(et.size(),0);
	
	
	vector<int> c(v);
	rep(i,v)cin>>c[i];
	
	dfs(0,-1,bt,c,st);	//初期の頂点の色を反映
	
	
	int q,q_type;
	cin>>q;
	rep(i,q){
		cin>>q_type;
		if(q_type==1){
			int u;
			cin>>u;
			u--;
			if(u==0)continue;
			bt.rev_cost(par[u],u,st);
		}else{
			int u,v;
			cin>>u>>v;
			u--,v--;
			if(bt.get_cost(u, v, st)==0)cout<<"YES"<<endl;
			else cout<<"NO"<<endl;
		}
	}
}