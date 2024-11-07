#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int largestCombination(vector<int>& candidates) {
        int retVal = 0;

        // 1 <= candidates[i] <= 10^7 < 2^24
        for (int i = 0; i < 24; ++i) {
            int maxCount = 0;
            for (int candidate : candidates) {
                if ((candidate & (1 << i)) != 0) {
                    maxCount++;
                }
            }
            retVal = max(retVal, maxCount);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> candidates;
    };
    vector<subject> testData{{{16, 17, 71, 62, 12, 24, 14}}, {{8, 8}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: candidates = [16,17,71,62,12,24,14]
     *  Output: 4
     *
     *  Input: candidates = [8,8]
     *  Output: 2
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: candidates = [";
        for (long unsigned int j = 0; j < testData[i].candidates.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].candidates[j];
        }
        cout << "]\n";

        answer = cSolution.largestCombination(testData[i].candidates);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
