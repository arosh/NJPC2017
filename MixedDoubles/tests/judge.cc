// Compare doubles allowing errors, ignoring the amount of whitespaces.

#include "testlib.h"
#include <iostream>
#include <iomanip>

using namespace std;

const bool kAllowAbsoluteError = true;
const bool kAllowRelativeError = true;

const long double kAcceptableAbsoluteError = 1.0e-6 + 1.0e-12;
const long double kAcceptableRelativeError = 1.0e-6 + 1.0e-12;

bool Equals(const long double expected, const long double actual) {
    if (kAllowAbsoluteError) {
        const long double expected_min = expected - kAcceptableAbsoluteError;
        const long double expected_max = expected + kAcceptableAbsoluteError;
        if (expected_min <= actual && actual <= expected_max) {
            return true;
        }
    }

    if (kAllowRelativeError) {
        const long double acceptable_error = expected * kAcceptableRelativeError;
        const long double expected_min = expected - acceptable_error;
        const long double expected_max = expected + acceptable_error;
        if (expected_min <= actual && actual <= expected_max) {
            return true;
        }
    }

    return (expected == actual);
}

int main(int argc, char **argv) {
    // registerTestlibCmd(argc, argv);
    // 引数の順番やら何やらが違うので以下を使う
    inf.init(argv[2], _input);
    ans.init(argv[4], _answer);
    ouf.init(argv[6], _output);

    int count = 0;
    while (!ans.seekEof()) {
        ++count;
        const double expected = ans.readDouble();
        const double actual = ouf.readDouble();
        if (!Equals(expected, actual)) {
            quitf(_wa, "- (%d%s value) expected: %.16f, actual: %.16f", count,
                        englishEnding(count).c_str(), expected, actual);
        }
        cout << fixed << setprecision(10) << "expected = " << expected
            << ", actual = " << actual << endl;
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "- extra tokens");
    }
    quitf(_ok, "- %d values", count);

    return 0;
}
