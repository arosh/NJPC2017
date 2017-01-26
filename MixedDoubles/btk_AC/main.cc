#include <cstdio>
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;
//struct INIT{INIT(){ios::sync_with_stdio(false);cin.tie(0);cout<<fixed;cout<<setprecision(11);}}init;
typedef double F;
const F INF=1e10;
const F eps=1e-15;
inline bool check(vector<double>& T,vector<double>& X,F v){
    int N=T.size();
    F lb=0,ub=0;
    for(int i = 1; i < N; i++){
        F nlb=INF,nub=-INF;
        F w = v * (T[i]-T[i-1]);
        if(X[i-1] - w - eps < X[i] && X[i] < X[i-1] + w + eps)
            nlb = min(lb - w,nlb),nub = max(ub + w,nub);
        if(lb - w - eps < X[i] && X[i] < ub + w + eps)
            nlb = min(X[i-1]- w ,nlb),nub = max(X[i-1] + w,nub);
        if(nub<nlb)return false;
        lb=nlb;
        ub=nub;
    }
    return true;
};

int main() {
    int N;
    scanf("%d",&N);
    vector<double> T(N+1),X(N+1);
    T[0] = X[0] = 0;
    for(int i = 1; i <= N; i++){
        scanf("%lf %lf",&T[i],&X[i]);
    }
    F can=INF,cannot=0;
    for(int i = 0; i < 100; i++){
        const F mid=(can+cannot)/2;
        if(check(T,X,mid))can=mid;else cannot=mid;
    }
    printf("%.11f\n",(double) (can+eps));
    return 0;
}
