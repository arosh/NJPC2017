#include "./testlib.h"
#include "./constraints.hpp"
#include <cassert>
#include <vector>
using namespace std;


class UF{
private:
	vector<int> par,rank,elm;
	vector<vector<int> > elmList;	//don't be validated
public:
	int groups;

	UF(int __size):par(__size) , rank(__size,0) , elm(__size,1) , groups(__size), elmList(__size){
		for(int i=0;i<__size;i++)elmList[i] = vector<int>(1,i);
		for(int i=0;i<__size;i++)par[i]=i;
	}

	int find(int x){
		if(par[x]==x) {
			return x;
		}else{
			return par[x]=find(par[x]);
		}
	}

	void unite(int x,int y){
		x=find(x);
		y=find(y);
		if(x==y) return;

		groups--;
		if(rank[x]<rank[y]){
			par[x]=y;
			elm[y]+=elm[x];
			for(auto &e:elmList[x])elmList[y].push_back(e);

		}else{
			par[y]=x;
			elm[x]+=elm[y];
			for(auto &e:elmList[y])elmList[x].push_back(e);
			if(rank[x]==rank[y])rank[x]++;
		}
	}

};


int main(){
    registerValidation();
	int N = inf.readInt(MIN_N, MAX_N);
	UF uf(N);
	inf.readEoln();
	for(int i=2;i<=N;i++){
		// int p = inf.readInt(MIN_Pi,MAX_Pi);
		int p = inf.readInt(1, N);
		inf.readEoln();
		uf.unite(p-1,i-1);
	}

	for(int i=1;i<=N;i++){
		inf.readInt(MIN_Ci,MAX_Ci);
		inf.readEoln();
	}

	bool query2_used=false;
	int Q = inf.readInt(MIN_Q,MAX_Q);
	inf.readEoln();
	for(int i=0;i<Q;i++){
		int query_type = inf.readInt(1,2);
		inf.readSpace();

		if(query_type==1){
			inf.readInt(1,N);
		}else if(query_type==2){
			query2_used = true;
			int u,v;
			u = inf.readInt(1,N);
			inf.readSpace();
			v = inf.readInt(1,N);
			assert(u!=v);
		}else abort();

		inf.readEoln();
	}
    inf.readEof();

    assert(query2_used==true);
    assert(uf.groups==1);
}
