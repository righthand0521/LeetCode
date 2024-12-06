#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxCount(vector<int>& banned, int n, int maxSum) {
        int retVal = 0;

        // Store banned numbers in an unordered_set
        unordered_set<int> bannedSet(banned.begin(), banned.end());

        for (int num = 1; num <= n; num++) {
            // Skip banned numbers
            if (bannedSet.count(num) != 0) {
                continue;
            }

            // Return if adding current number exceeds maxSum
            if (maxSum - num < 0) {
                break;
            }

            // Include current number
            maxSum -= num;
            retVal++;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> banned;
        int n;
        int maxSum;
    };
    vector<subject> testData{{{1, 6, 5}, 5, 6}, {{1, 2, 3, 4, 5, 6, 7}, 8, 1}, {{11}, 7, 50}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: banned = [1,6,5], n = 5, maxSum = 6
     *  Output: 2
     *
     *  Input: banned = [1,2,3,4,5,6,7], n = 8, maxSum = 1
     *  Output: 0
     *
     *  Input: banned = [11], n = 7, maxSum = 50
     *  Output: 7
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: banned = [";
        for (long unsigned int j = 0; j < testData[i].banned.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].banned[j];
        }
        cout << "], n = " << testData[i].n << ", maxSum = " << testData[i].maxSum << "\n";

        answer = cSolution.maxCount(testData[i].banned, testData[i].n, testData[i].maxSum);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
