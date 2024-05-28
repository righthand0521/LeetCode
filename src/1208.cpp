#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int equalSubstring(string s, string t, int maxCost) {
        int retVal = 0;

        int sSize = s.size();

        int cost = 0;
        int start = 0;
        int end = 0;
        for (end = 0; end < sSize; ++end) {
            cost += abs(s[end] - t[end]);
            while (cost > maxCost) {
                cost -= abs(s[start] - t[start]);
                start += 1;
            }
            retVal = max(retVal, end - start + 1);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
        string t;
        int maxCost;
    };
    vector<subject> testData{{"abcd", "bcdf", 3}, {"abcd", "cdef", 3}, {"abcd", "acde", 0}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "abcd", t = "bcdf", maxCost = 3
     *  Output: 3
     *
     *  Input: s = "abcd", t = "cdef", maxCost = 3
     *  Output: 1
     *
     *  Input: s = "abcd", t = "acde", maxCost = 0
     *  Output: 1
     */

    Solution cSolution;
    int answer = 0;
    for (int x = 0; x < numberOfTestCase; ++x) {
        cout << "Input: s = \"" << testData[x].s << "\", ";
        cout << "t = \"" << testData[x].t << "\", ";
        cout << "maxCost = " << testData[x].maxCost << "\n";

        answer = cSolution.equalSubstring(testData[x].s, testData[x].t, testData[x].maxCost);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
