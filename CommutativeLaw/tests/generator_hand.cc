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
void output(const string &s, const string &prefix, int num){
    char name[100];
    sprintf(name, "%s_%02d.in", prefix.c_str(), num);
    ofstream ofs(name);
    ofs << s << endl;
    ofs.close();
}

int main(){
    rnd.setSeed(711);

    int num = 0;

    rep(t, 2) {
        char x = (t ? 'a' : 'b');
        char y = (t ? 'b' : 'a');

        // aa...ab
        output(string(MAX_L - 1, x) + y, "97_max", num++);

        // abb...b
        output(x + string(MAX_L - 1, y), "97_max", num++);

        // abab...ab
        string s;
        for (int i = 0; i < MAX_L - 1; i += 2) {
            s += x; s += y;
        }
        output(s, "97_max", num++);
    }
}
