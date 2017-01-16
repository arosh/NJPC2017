#include "./testlib.h"
#include "./constraints.hpp"
#include <cassert>

int main(){
    registerValidation();
    inf.readInt(MIN_L, MAX_L,"n");
    inf.readEoln();
    inf.readToken("[a-z]{MIN_L,MAX_L}", "s");
    inf.readEoln();
    inf.readEof();
}
