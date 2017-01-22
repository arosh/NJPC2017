#include <iostream>
#include <utility>
#include "./testlib.h"
#include "./constraints.hpp"
#include <sys/types.h>
#include <unistd.h>
#include <random>
#include <cassert>

using namespace std;

#define rep(i,n) for(int i=0;i<(int)(n);i++)

// aとbをファイルストリームに出力する
// ファイル名は prefix_num.in (ex: 00_sample_00.in)
void output(int a, int b, vector<int> X, const string &prefix, int num){
    char name[100];
    sprintf(name, "%s_%03d.in", prefix.c_str(), num);
    ofstream ofs(name);
    ofs << a << " " << b << endl;
    rep(i,X.size()){
        ofs << X[i] << endl;
    }
    ofs.close();
}

int main(){
    // 乱数のシードを設定
    // pidを足すことで、1秒以上間を置かずに起動したときに同じシードになってしまうのを防ぐ
    rnd.setSeed(time(0)+getpid());

    #define NUM_CASE 100

    // Xiの大きいケース(普通のランダムケース)をNUM_CASE個生成
    for(int case_num = 0; case_num < NUM_CASE; ++case_num){
        int N = rnd.next(MIN_N, MAX_N);
        int L = rnd.next(MIN_L, MAX_L);
        vector<int> X(N);
        while(1){
            for(int i=0;i<N;i++){
                X[i] = rnd.next(MIN_Xi, MAX_Xi);
            }
            sort(X.begin(),X.end());
            bool valid = true;
            for(int j=0;j<X.size()-1;j++){
                if(X[j]==X[j+1])valid = false;
            }
            if(valid)break;
        }
        output(N, L, X, "50_random_Xilarge", case_num);
    }


    // Xi,Nの小さいケースをNUM_CASE個生成
    vector<int> numbers(MAX_Xi_SMALL);
    for(int i=0;i<numbers.size();i++)numbers[i]=i+1;
    for(int case_num = 0; case_num < NUM_CASE; ++case_num){
        int N = rnd.next(MIN_N, MAX_N_SMALL);
        int L = rnd.next(MIN_L, MAX_L);
        shuffle(numbers.begin(),numbers.end());

        vector<int> X(N);
        for(int i=0;i<N;i++){
            X[i] = numbers[i];
        }
        sort(X.begin(),X.end());

        output(N, L, X, "50_random_XiNsmall", case_num);

    }


    // Xiが大きく、LがきわどいケースをNUM_CASE個生成
    for(int case_num = 0; case_num < NUM_CASE; ++case_num){
        int N = rnd.next(MIN_N, MAX_N);
        vector<int> X(N);
        while(1){
            for(int i=0;i<N;i++){
                X[i] = rnd.next(MIN_Xi, MAX_Xi);
            }
            sort(X.begin(),X.end());
            bool valid = true;
            for(int j=0;j<X.size()-1;j++){
                if(X[j]==X[j+1])valid = false;
            }
            if(valid)break;
        }
        int L = X[rnd.next(0, (int)X.size()-1)]+rnd.next(0,2);
        output(N, L, X, "50_random_Xilarge_narrow", case_num);
    }


    // Xi,Nが小さく、LがきわどいケースをNUM_CASE個生成
    for(int case_num = 0; case_num < NUM_CASE; ++case_num){
        int N = rnd.next(MIN_N, MAX_N_SMALL);
        shuffle(numbers.begin(),numbers.end());

        vector<int> X(N);
        for(int i=0;i<N;i++){
            X[i] = numbers[i];
        }
        sort(X.begin(),X.end());

        int L = X[rnd.next(0, (int)X.size()-1)]+rnd.next(0,2);
        output(N, L, X, "50_random_XiNsmall_narrow", case_num);
    }


    // N,Lの小さいケースをNUM_CASE個生成
    for(int case_num = 0; case_num < NUM_CASE; ++case_num){
        int N = rnd.next(MIN_N, MAX_N_SMALL);
        int L = rnd.next(MIN_L, MAX_L_SMALL);
        shuffle(numbers.begin(),numbers.end());

        vector<int> X(N);
        for(int i=0;i<N;i++)X[i] = numbers[i];
        sort(X.begin(),X.end());

        output(N, L, X, "50_random_NLsmall", case_num);

    }


    // X1<LのケースをNUM_CASE個生成
    for(int case_num = 0; case_num < NUM_CASE; ++case_num){
        int N = rnd.next(MIN_N, MAX_N);
        int L = rnd.next(MIN_L+1, MAX_L);
        vector<int> X(N);
        while(1){
            for(int i=0;i<N;i++){
                X[i] = rnd.next(MIN_Xi,MAX_Xi);
            }
            sort(X.begin(),X.end());
            bool valid = true;
            for(int j=0;j<X.size()-1;j++){
                if(X[j]==X[j+1])valid = false;
            }
            if(valid)break;
        }
        if(X[0]>=L)X[0] = rnd.next(1,X[0]-1);
        output(N, L, X, "50_random_x1small", case_num);
    }
}
