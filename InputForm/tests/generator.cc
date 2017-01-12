#include "./constraints.hpp"
#include "./testlib.h"
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

struct FileName {
  const int id;
  const string name;
  int done = 0;

  FileName(const int id, const string name) : id(id), name(name) {
    return;
  }

  string operator()() {
    ostringstream oss;
    oss << std::setfill('0') << setw(2) << id << '_' << name << '_' << setw(2) << done << ".in";
    done++;
    return oss.str();
  }
};

void Write(const string &name, const int L, const string &S) {
  ofstream fs(name);
  fs << L << endl;
  fs << S << endl;
}

int main(int argc, char *argv[]) {
  // Use registerGen(argc, argv, 1) to develop new generator
  registerGen(argc, argv, 1);
  FileName fileName(50, "random");
  for(int i = 0; i < 20; i++) {
    rnd.setSeed(16 + i);
    const int L = rnd.next(MIN_L, MAX_L);
    const string S = rnd.next("[a-z]{%d}", rnd.next(MIN_L, MAX_L));
    Write(fileName(), L, S);
  }
}
