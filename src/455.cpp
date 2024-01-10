#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        int retVal = 0;

        int gSize = g.size();
        sort(g.begin(), g.end());
        int gIdx = 0;

        int sSize = s.size();
        sort(s.begin(), s.end());
        int sIdx = 0;

        while ((gIdx < gSize) && (sIdx < sSize)) {
            if (g[gIdx] <= s[sIdx]) {
                ++gIdx;
                ++retVal;
            }
            ++sIdx;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> g;
        vector<int> s;
    };
    vector<subject> testData{{{1, 2, 3}, {1, 1}}, {{1, 2}, {1, 2, 3}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: g = [1,2,3], s = [1,1]
     *  Output: 1
     *
     *  Input: g = [1,2], s = [1,2,3]
     *  Output: 2
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: g = [";
        for (long unsigned int j = 0; j < testData[i].g.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].g[j];
        }
        cout << "], s = [";
        for (long unsigned int j = 0; j < testData[i].s.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].s[j];
        }
        cout << "]\n";

        answer = cSolution.findContentChildren(testData[i].g, testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
