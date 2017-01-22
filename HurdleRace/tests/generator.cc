Skip to content
This repository
Search
Pull requests
Issues
Gist
 @yurahuna
 Unwatch 5
  Star 1
  Fork 0 Yazaten/NJPC2017 Private
 Code  Issues 9  Pull requests 0  Projects 0  Wiki  Pulse  Graphs
Branch: master Find file Copy pathNJPC2017/HurdleRace/tests/generator.cc
f360651  16 minutes ago
@Yazaten Yazaten ハードル走のgeneratorで部分点ケースも生成するように変更した
1 contributor
RawBlameHistory
179 lines (153 sloc)  5.3 KB
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
    sprintf(name, "%s_%02d.in", prefix.c_str(), num);
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

    // ランダムケース(MAX_N,MAX_L,MAX_Xi)
    for(int case_num = 0; case_num < 10; ++case_num){
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

    // ランダムケース(MAX_N_SMALL,MAX_L,MAX_Xi_PART)
    vector<int> numbers(MAX_Xi_PART);
    for(int i=0;i<numbers.size();i++)numbers[i]=i+1;
    for(int case_num = 0; case_num < 10; ++case_num){
        int N = rnd.next(MIN_N_SMALL, MAX_N_SMALL);
        int L = rnd.next(MIN_L, MAX_L);
        shuffle(numbers.begin(),numbers.end());

        vector<int> X(N);
        for(int i=0;i<N;i++){
            X[i] = numbers[i];
        }
        sort(X.begin(),X.end());

        output(N, L, X, "50_random_XiNsmall", case_num);

    }

    //部分点
    // ランダムケース(MAX_N_SMALL,MAX_L_PART,MAX_Xi_PART)
    for(int case_num = 0; case_num < 10; ++case_num){
        int N = rnd.next(MIN_N_PART, MAX_N_PART);
        int L = rnd.next(MIN_L_PART, MAX_L_PART);
        shuffle(numbers.begin(),numbers.end());

        vector<int> X(N);
        for(int i=0;i<N;i++){
            X[i] = numbers[i];
        }
        sort(X.begin(),X.end());

        output(N, L, X, "50_random_XiNsmall_part", case_num);

    }


    // Lがきわどいケース(MAX_N,MAX_L,MAX_Xi)
    for(int case_num = 0; case_num < 10; ++case_num){
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
        int L = min(MAX_L,X[rnd.next(0, (int)X.size()-1)]+rnd.next(0,2));
        output(N, L, X, "50_random_Xilarge_narrow", case_num);
    }

    //部分点
    // Lがきわどいケース(MAX_N_SMALL,MAX_L_PART,MAX_Xi_PART)
    for(int case_num = 0; case_num < 10; ++case_num){
        int N = rnd.next(MIN_N_SMALL, MAX_N_SMALL);
        shuffle(numbers.begin(),numbers.end());

        vector<int> X(N);
        for(int i=0;i<N;i++){
            X[i] = numbers[i];
        }
        sort(X.begin(),X.end());

        int L = min(MAX_L_PART,X[rnd.next(0, (int)X.size()-1)]+rnd.next(0,2));
        output(N, L, X, "50_random_XiNsmall_narrow_part", case_num);
    }

    //部分点
    // N,Lの小さいケース(MAX_N_SMALL,MAX_L_PART,MAX_L_PART)
    for(int case_num = 0; case_num < 10; ++case_num){
        int N = rnd.next(MIN_N_SMALL, MAX_N_SMALL);
        int L = rnd.next(MIN_L_PART, MAX_L_PART);
        shuffle(numbers.begin(),numbers.end());

        vector<int> X(N);
        for(int i=0;i<N;i++)X[i] = numbers[i];
        sort(X.begin(),X.end());

        output(N, L, X, "50_random_NLsmall_part", case_num);

    }


    // X1<Lのケース(MAX_N,MAX_L,MAX_Xi)
    for(int case_num = 0; case_num < 10; ++case_num){
        int N = rnd.next(MIN_N, MAX_N);
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
        int L = min(MAX_L,x[0]);
        if(X[0]>=L)X[0] = rnd.next(1,X[0]-1);
        output(N, L, X, "50_random_x1small", case_num);
    }

    //部分点
    // X1<Lのケース(MAX_N_PART,MAX_L_PART,MAX_Xi_PART)
    for(int case_num = 0; case_num < 10; ++case_num){
        int N = rnd.next(MIN_N_PART, MAX_N_PART);
        vector<int> X(N);
        while(1){
            for(int i=0;i<N;i++){
                X[i] = rnd.next(MIN_Xi_PART,MAX_Xi_PART);
            }
            sort(X.begin(),X.end());
            bool valid = true;
            for(int j=0;j<X.size()-1;j++){
                if(X[j]==X[j+1])valid = false;
            }
            if(valid)break;
        }
        int L = min(MAX_L_PART,x[0]);
        if(X[0]>=L)X[0] = rnd.next(1,X[0]-1);
        output(N, L, X, "50_random_x1small_part", case_num);
    }
}
Contact GitHub API Training Shop Blog About
© 2017 GitHub, Inc. Terms Privacy Security Status Help
