#include "./testlib.h"
#include "./constraints.hpp"
#include <cstdio>

int main(){
    registerValidation();
    char re[100];
    sprintf(re,"[a-z]{%d,%d}",MIN_L,MAX_L);
    inf.readToken(re,"s");
    inf.readEoln();
    inf.readEof();
}