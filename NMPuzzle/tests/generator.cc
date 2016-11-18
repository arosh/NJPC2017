#include <iostream>
#include <utility>
#include "./testlib.h"
#include "./constraints.hpp"
#include <sys/types.h>
#include <unistd.h>

using namespace std;

#define rep(i,n) for(int i=0;i<(int)(n);i++)

// ケースをファイルストリームに出力する
// ファイル名は prefix_num.in (ex: 00_sample_00.in)
void output(int N, int M, int K, const string &prefix, int num){
    char name[100];
    sprintf(name, "%s_%02d.in", prefix.c_str(), num);
    ofstream ofs(name);
    ofs << N << " " << M << " " << K << endl;
    ofs.close();
}

// 制約に沿ってKの最大値を返す
int maxK(int N, int M) {
    return M*N*(N-1)/2 + N*M*(N-1)/2;
}

int main(){
    // 乱数のシードを設定
    // pidを足すことで、1秒以上間を置かずに起動したときに同じシードになってしまうのを防ぐ
    rnd.setSeed(time(0)+getpid());

    // 乱数ケースを10個生成
    for(int i = 0; i < 10; ++i){
        int N = rnd.next(MIN_N, MAX_N);
        int M = rnd.next(MIN_M, MAX_M);
        int K = rnd.next(MIN_K, maxK(N, M));
        output(A, B, "10_random", i);
    }

    // N, Mのうち片方が大きいケースを10個生成
    for(int i = 0; i < 10; ++i){
        int N = 1;
        int M = 1;
        while(0.5*N <= M && M <= 1.5*N){
            N = rnd.next(MIN_N, MAX_N);
            M = rnd.next(MIN_M, MAX_M);
        }
        if(rnd.next(0,1)) swap(A, B);
        int K = rnd.next(MIN_K, maxK(N, M));
        output(A, B, "20_unbalance_NM", i);
    }

    // Kが最小側に偏ったケースを5個生成
    for(int i = 0; i < 10; ++i){
        int N = rnd.next(MIN_N, MAX_N);
        int M = rnd.next(MIN_M, MAX_M);
        int K = rnd.next(MIN_K, min(maxK(N, M), 10));
        output(A, B, "30_nearly_minimum_K", i);
    }

    // Kが最大側に偏ったケースを5個生成
    for(int i = 0; i < 10; ++i){
        int N = rnd.next(MIN_N, MAX_N);
        int M = rnd.next(MIN_M, MAX_M);
        int K = rnd.next(MIN_K, max(0, maxK(N, M) - 10));
        output(A, B, "40_nearly_maximum_K", i);
    }

    // Kが真ん中に偏ったケースを5個生成
    for(int i = 0; i < 10; ++i){
        int N = rnd.next(MIN_N, MAX_N);
        int M = rnd.next(MIN_M, MAX_M);
        int K = rnd.next(max(MIN_K, maxK(N, M) / 2 - 10), min(maxK(N, M), maxK(N, M) / 2 + 10));
        output(A, B, "50_nearly_middle_K", i);
    }

}
