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
    // rnd.setSeed(time(0)+getpid());
    rnd.setSeed(711);

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


    // X0<=Lのケース(MAX_N,MAX_L,MAX_Xi)
    for(int case_num = 0; case_num < 10; ++case_num){
        int N = rnd.next(MIN_N, MAX_N);
        int L = rnd.next(MIN_L, MAX_L);
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
        if(X[0]>L)L = min(MAX_L,rnd.next(1,X[0]));

        output(N, L, X, "50_random_x0small", case_num);
    }

    //部分点
    // X1<Lのケース(MAX_N_PART,MAX_L_PART,MAX_Xi_PART)
    for(int case_num = 0; case_num < 10; ++case_num){
        int N = rnd.next(MIN_N_PART, MAX_N_PART);
        int L = rnd.next(MIN_L_PART, MAX_L_PART);
        shuffle(numbers.begin(),numbers.end());

        vector<int> X(N);
        for(int i=0;i<N;i++)X[i] = numbers[i];
        sort(X.begin(),X.end());

        if(X[0]>L)L = min(MAX_L_PART,rnd.next(1,X[0]));

        output(N, L, X, "50_random_x1small_part", case_num);
    }
}
