#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
   private:
    void add(int a, string& t, int start) {
        int minVal = 10;
        int times = 0;
        for (int i = 0; i < 10; i++) {
            int added = ((t[start] - '0') + i * a) % 10;
            if (added < minVal) {
                minVal = added;
                times = i;
            }
        }

        int tSize = t.size();
        for (int i = start; i < tSize; i += 2) {
            t[i] = '0' + ((t[i] - '0') + times * a) % 10;
        }
    }

   public:
    string findLexSmallestString(string s, int a, int b) {
        string retVal = s;

        int sSize = s.size();

        s = s + s;
        int g = gcd(b, sSize);
        for (int i = 0; i < sSize; i += g) {
            string t = s.substr(i, sSize);
            add(a, t, 1);
            if (b % 2) {
                add(a, t, 0);
            }
            retVal = min(retVal, t);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
        int a;
        int b;
    };
    vector<subject> testData{{"5525", 9, 2}, {"74", 5, 1}, {"0011", 4, 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "5525", a = 9, b = 2
     *  Output: "2050"
     *
     *  Input: s = "74", a = 5, b = 1
     *  Output: "24"
     *
     *  Input: s = "0011", a = 4, b = 2
     *  Output: "0011"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\", a = " << testData[i].a << ", b = " << testData[i].b << "\n";

        answer = cSolution.findLexSmallestString(testData[i].s, testData[i].a, testData[i].b);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
