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
    return N * M * (M-1)/2 + M * N * (N-1)/2;
}

int main(){
    // 乱数のシードを設定
    // pidを足すことで、1秒以上間を置かずに起動したときに同じシードになってしまうのを防ぐ
    // rnd.setSeed(time(0)+getpid());
    rnd.setSeed(711);

    // 乱数ケースを10個生成
    for(int i = 0; i < 10; ++i){
        int N = rnd.next(MIN_N, MAX_N);
        int M = rnd.next(MIN_M, MAX_M);
        int K = rnd.next(MIN_K, maxK(N, M));
        output(N, M, K, "10_random", i);
    }

    // N, Mのうち片方が大きいケースを10個生成
    for(int i = 0; i < 10; ++i){
        int N = 1;
        int M = 1;
        while(0.5*N <= M && M <= 1.5*N){
            N = rnd.next(MIN_N, MAX_N);
            M = rnd.next(MIN_M, MAX_M);
        }
        if(rnd.next(0,1)) swap(N, M);
        int K = rnd.next(MIN_K, maxK(N, M));
        output(N, M, K, "20_unbalance_NM", i);
    }

    // N, Mが大きく偏ったケースを10個生成
    for(int i = 0; i < 10; ++i){
        int N = rnd.next(MIN_N, 10);
        int M = rnd.next(MIN_M, MAX_M);
        if(rnd.next(0,1)) swap(N, M);
        int K = rnd.next(MIN_K, maxK(N, M));
        output(N, M, K, "30_very_unbalance_NM", i);
    }

    // N==Mのケースを10個生成
    for(int i = 0; i < 10; ++i){
        int N = rnd.next(MIN_N, MAX_N);
        int M = N;
        int K = rnd.next(MIN_K, maxK(N, M));
        output(N, M, K, "40_equal_NM", i);
    }

    // Kが最小側に偏ったケースを10個生成
    for(int i = 0; i < 10; ++i){
        int N = rnd.next(MIN_N, MAX_N);
        int M = rnd.next(MIN_M, MAX_M);
        int K = rnd.next(MIN_K, min(maxK(N, M), 10));
        output(N, M, K, "50_nearly_minimum_K", i);
    }

    // Kが最大側に偏ったケースを10個生成
    for(int i = 0; i < 10; ++i){
        int N = rnd.next(MIN_N, MAX_N);
        int M = rnd.next(MIN_M, MAX_M);
        int K = rnd.next(MIN_K, max(0, maxK(N, M) - 10));
        output(N, M, K, "60_nearly_maximum_K", i);
    }

    // Kが真ん中に偏ったケースを10個生成
    for(int i = 0; i < 10; ++i){
        int N = rnd.next(MIN_N, MAX_N);
        int M = rnd.next(MIN_M, MAX_M);
        int K = rnd.next(max(MIN_K, maxK(N, M) / 2 - 10), min(maxK(N, M), maxK(N, M) / 2 + 10));
        output(N, M, K, "70_nearly_middle_K", i);
    }

    // サンプルケース
    // output(2, 3, 5, "00_sample", 0);

    // ハンドケース
    // 何かあったら追加して
    // Kが行・列の端に偏ったケース？？(実装によっては落ちそう)
//    output(158, 27, 0, "80_hand", 0);
    output(1, 5, 10, "80_hand", 1);
    output(3, 3, 17, "80_hand", 2);
    output(3, 3, 3, "80_hand", 3);
    output(3, 3, 4, "80_hand", 4);

    // 最小・最大ケース
    output(MIN_N, MIN_M, MIN_K, "99_min_NMK", 0);
    output(MAX_N, MAX_M, MIN_K, "99_max_NM_min_K", 1);
    output(MAX_N, MAX_M, maxK(MAX_N, MAX_M), "99_max_NMK", 2);
    for(int i = 0; i < 5; ++i){
        int N = MAX_N;
        int M = MAX_M;
        int K = rnd.next(MIN_K, maxK(N, M));
        output(N, M, K, "99_max_NM_rand_K", i + 3);
    }

}
