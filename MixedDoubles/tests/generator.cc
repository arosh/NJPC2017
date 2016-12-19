#include <iostream>
#include <utility>
#include "./testlib.h"
#include "./constraints.hpp"
#include <sys/types.h>
#include <unistd.h>
#include <set>
#include <vector>

using namespace std;

#define rep(i,n) for(int i=0;i<(int)(n);i++)

// aとbをファイルストリームに出力する
// ファイル名は prefix_num.in (ex: 00_sample_00.in)
void output(int N, const set<int>& stT, const vector<int>& X, const string &prefix, int num){
    char name[100];
    sprintf(name, "%s_%02d.in", prefix.c_str(), num);
    ofstream ofs(name);
    ofs << N << endl;
    vector<int> T(stT.begin(), stT.end());
    rep(i, N) {
        ofs << T[i] << " " << X[i] << endl;
    }
    ofs.close();
}

int main(){
    // 乱数のシードを設定
    // pidを足すことで、1秒以上間を置かずに起動したときに同じシードになってしまうのを防ぐ
    rnd.setSeed(time(0)+getpid());

    for (int t = 1; t >= 0; t--) {
        // t = 1: 満点ケース
        // t = 0: 部分点ケース

        const int MAX_N = (t ? MAX_N_large : MAX_N_small);

        // 乱数ケースを10個生成
        for(int i = 0; i < 10; ++i){
            int N = rnd.next(MIN_N, MAX_N);
            set<int> T;
            while ((int)T.size() < N) {
                int t = rnd.next(MIN_T, MAX_T);
                if (T.count(t)) continue;
                T.insert(t);
            }
            vector<int> X(N);
            rep(j, N) X[j] = rnd.next(MIN_X, MAX_X);
            output(N, T, X, to_string(t) + "1_random", i);
        }

        // 位置が正に偏るケースを5個生成
        for(int i = 0; i < 5; ++i){
            int N = rnd.next(MIN_N, MAX_N);
            set<int> T;
            while ((int)T.size() < N) {
                int t = rnd.next(MIN_T, MAX_T);
                if (T.count(t)) continue;
                T.insert(t);
            }
            vector<int> X(N);
            rep(j, N) X[j] = rnd.next(-100, MAX_X);
            output(N, T, X, to_string(t) + "2_X_positive", i);
        }

        // 位置が負に偏るケースを5個生成
        for(int i = 0; i < 5; ++i){
            int N = rnd.next(MIN_N, MAX_N);
            set<int> T;
            while ((int)T.size() < N) {
                int t = rnd.next(MIN_T, MAX_T);
                if (T.count(t)) continue;
                T.insert(t);
            }
            vector<int> X(N);
            rep(j, N) X[j] = rnd.next(MIN_X, 100);
            output(N, T, X, to_string(t) + "3_X_negative", i);
        }

        // Tが小さいケースを5個生成
        for(int i = 0; i < 5; ++i){
            int N = rnd.next(MIN_N, MAX_N);
            set<int> T;
            while ((int)T.size() < N) {
                int t = rnd.next(MIN_T, 100000);
                if (T.count(t)) continue;
                T.insert(t);
            }
            vector<int> X(N);
            rep(j, N) X[j] = rnd.next(MIN_X, MAX_X);
            output(N, T, X, to_string(t) + "4_T_small", i);
        }

        // 正負を何百回かずつ

        // Tが大きいケースを5個生成
        for(int i = 0; i < 5; ++i){
            int N = rnd.next(MIN_N, MAX_N);
            set<int> T;
            while ((int)T.size() < N) {
                int t = rnd.next(100000000, MAX_T);
                if (T.count(t)) continue;
                T.insert(t);
            }
            vector<int> X(N);
            rep(j, N) X[j] = rnd.next(MIN_X, MAX_X);
            output(N, T, X, to_string(t) + "4_T_large", i);
        }

        // |X|が小さいケースを5個生成
        for(int i = 0; i < 5; ++i){
            int N = rnd.next(MIN_N, MAX_N);
            set<int> T;
            while ((int)T.size() < N) {
                int t = rnd.next(MIN_T, MAX_T);
                if (T.count(t)) continue;
                T.insert(t);
            }
            vector<int> X(N);
            rep(j, N) X[j] = rnd.next(-100, 100);
            output(N, T, X, to_string(t) + "5_absX_small", i);
        }

        // |X|が大きいケースを5個生成
        for(int i = 0; i < 5; ++i){
            int N = rnd.next(MIN_N, MAX_N);
            set<int> T;
            while ((int)T.size() < N) {
                int t = rnd.next(MIN_T, MAX_T);
                if (T.count(t)) continue;
                T.insert(t);
            }
            vector<int> X(N);
            rep(j, N) X[j] = rnd.next(100000, MAX_X) * (rnd.next(2) ? +1 : -1);
            output(N, T, X, to_string(t) + "5_absX_large", i);
        }

        // Xが正の方向に大きいケースを5個生成
        for(int i = 0; i < 5; ++i){
            int N = rnd.next(MIN_N, MAX_N);
            set<int> T;
            while ((int)T.size() < N) {
                int t = rnd.next(MIN_T, MAX_T);
                if (T.count(t)) continue;
                T.insert(t);
            }
            vector<int> X(N);
            rep(j, N) X[j] = rnd.next(100000, MAX_X);
            output(N, T, X, to_string(t) + "5_X_positive_large", i);
        }

        // Xが負の方向に大きいケースを5個生成
        for(int i = 0; i < 5; ++i){
            int N = rnd.next(MIN_N, MAX_N);
            set<int> T;
            while ((int)T.size() < N) {
                int t = rnd.next(MIN_T, MAX_T);
                if (T.count(t)) continue;
                T.insert(t);
            }
            vector<int> X(N);
            rep(j, N) X[j] = -1 * rnd.next(100000, MAX_X);
            output(N, T, X, to_string(t) + "5_X_negative_large", i);
        }

        // 最大ケース
        int num = 0;

        // Nは最大, N以外乱数のケースを3つ
        for(int i = 0; i < 3; ++i){
            int N = MAX_N;
            set<int> T;
            while ((int)T.size() < N) {
                int t = rnd.next(MIN_T, MAX_T);
                if (T.count(t)) continue;
                T.insert(t);
            }
            vector<int> X(N);
            rep(j, N) X[j] = rnd.next(MIN_X, MAX_X);
            output(N, T, X, to_string(t) + "9_max", num++);
        }

        // だんだん右・左に進んでいくケース
        {
            int N = MAX_N;
            set<int> T;
            while ((int)T.size() < N) {
                int t = rnd.next(MIN_T, MAX_T);
                if (T.count(t)) continue;
                T.insert(t);
            }
            vector<int> X(N);
            rep(j, N) X[j] = rnd.next(0, MAX_X);
            sort(X.begin(), X.end());
            output(N, T, X, to_string(t) + "9_max", num++);
        }
        {
            int N = MAX_N;
            set<int> T;
            while ((int)T.size() < N) {
                int t = rnd.next(MIN_T, MAX_T);
                if (T.count(t)) continue;
                T.insert(t);
            }
            vector<int> X(N);
            rep(j, N) X[j] = rnd.next(MIN_X, 0);
            sort(X.rbegin(), X.rend());
            output(N, T, X, to_string(t) + "9_max", num++);
        }

        // ずっと原点・右端・左端
        {
            int N = MAX_N;
            set<int> T;
            while ((int)T.size() < N) {
                int t = rnd.next(MIN_T, MAX_T);
                if (T.count(t)) continue;
                T.insert(t);
            }
            vector<int> X(N, 0);
            output(N, T, X, to_string(t) + "9_max", num++);
        }
        {
            int N = MAX_N;
            set<int> T;
            while ((int)T.size() < N) {
                int t = rnd.next(MIN_T, MAX_T);
                if (T.count(t)) continue;
                T.insert(t);
            }
            vector<int> X(N, MAX_X);
            output(N, T, X, to_string(t) + "9_max", num++);
        }
        {
            int N = MAX_N;
            set<int> T;
            while ((int)T.size() < N) {
                int t = rnd.next(MIN_T, MAX_T);
                if (T.count(t)) continue;
                T.insert(t);
            }
            vector<int> X(N, MIN_X);
            output(N, T, X, to_string(t) + "9_max", num++);
        }

        // 右端と左端交互
        {
            int N = MAX_N;
            set<int> T;
            while ((int)T.size() < N) {
                int t = rnd.next(MIN_T, MAX_T);
                if (T.count(t)) continue;
                T.insert(t);
            }
            vector<int> X(N);
            rep(j, N) X[j] = (j % 2 ? MIN_X : MAX_X);
            output(N, T, X, to_string(t) + "9_max", num++);
        }

        // 右端と左端を1秒ずつに交互(速度最大のケース)
        {
            int N = MAX_N;
            set<int> T;
            while ((int)T.size() < N) {
                T.insert((int)T.size() + 1);
            }
            vector<int> X(N);
            rep(j, N) X[j] = (j % 2 ? MIN_X : MAX_X);
            output(N, T, X, to_string(t) + "9_max", num++);
        }

        // 1秒ずつ右・左へ
        {
            int N = MAX_N;
            set<int> T;
            while ((int)T.size() < N) {
                T.insert((int)T.size() + 1);
            }
            vector<int> X(N);
            rep(j, N) X[j] = rnd.next(0, MAX_X);
            sort(X.begin(), X.end());
            output(N, T, X, to_string(t) + "9_max", num++);
        }
        {
            int N = MAX_N;
            set<int> T;
            while ((int)T.size() < N) {
                T.insert((int)T.size() + 1);
            }
            vector<int> X(N);
            rep(j, N) X[j] = rnd.next(MIN_X, 0);
            sort(X.rbegin(), X.rend());
            output(N, T, X, to_string(t) + "9_max", num++);
        }

        // 1秒ずつ位置ランダム
        {
            int N = MAX_N;
            set<int> T;
            while ((int)T.size() < N) {
                T.insert((int)T.size() + 1);
            }
            vector<int> X(N);
            rep(j, N) X[j] = rnd.next(MIN_X, MAX_X);
            output(N, T, X, to_string(t) + "9_max", num++);
        }
    }

    // N=1
    rep(i, 3) {
        int N = 1;
        set<int> T;
        while ((int)T.size() < N) {
            int t = rnd.next(MIN_T, MAX_T);
            if (T.count(t)) continue;
            T.insert(t);
        }
        vector<int> X(N);
        rep(j, N) X[j] = rnd.next(MIN_X, MAX_X);
        sort(X.rbegin(), X.rend());
        output(N, T, X, "08_N=1", i);
    }

    // 速度が0でなく絶対値最小のケース
    int N = 1;
    set<int> T;
    T.insert(MAX_T);
    vector<int> X(1, 1);
    output(N, T, X, "08_V_minimum_nonzero", 0);
}
