#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

// https://leetcode.com/problems/check-if-digits-are-equal-in-string-after-operations-ii/solutions/6457845/python-check-mod2-and-mod5/
class Solution {
   private:
    vector<int> cal(int a, int mod) {
        vector<int> retVal(2, 0);

        int count = 0;
        while ((a > 0) && (a % mod == 0)) {
            count += 1;
            a /= mod;
        }
        retVal[0] = a % mod;
        retVal[1] = count;

        return retVal;
    }
    bool test(string s, int mod) {
        bool retVal = true;

        int sSize = s.size();

        long long res = 0;
        long long r = 1;
        int c = 0;
        for (int i = 0; i < sSize - 1; ++i) {
            if (c == 0) {
                res += (r * (static_cast<int>(s[i] - '0') - static_cast<int>(s[i + 1] - '0')));
            }

            vector<int> calResult = cal(sSize - 2 - i, mod);
            r = r * calResult[0] % mod;
            c += calResult[1];

            calResult = cal(i + 1, mod);
            r = r * static_cast<long long>(pow(calResult[0], mod - 2)) % mod;
            c -= calResult[1];
        }

        retVal = (res % mod == 0);

        return retVal;
    }

   public:
    bool hasSameDigits(string s) {
        bool retVal = true;

        retVal = test(s, 2) && test(s, 5);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"3902"}, {"34789"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "3902"
     *  Output: true
     *
     *  Input: s = "34789"
     *  Output: false
     */

    Solution cSolution;
    bool answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.hasSameDigits(testData[i].s);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
