#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int main() {
  int L; string S;
  cin >> L >> S;
  cout << S.substr(0, min<int>(L, S.size())) << endl;
}
