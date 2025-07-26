#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   public:
    long long maxSubarrays(int n, vector<vector<int>>& conflictingPairs) {
        long long retVal = 0;

        vector<int> bMin1(n + 1, numeric_limits<int>::max());
        vector<int> bMin2(n + 1, numeric_limits<int>::max());
        for (const auto& pair : conflictingPairs) {
            int a = min(pair[0], pair[1]);
            int b = max(pair[0], pair[1]);
            if (bMin1[a] > b) {
                bMin2[a] = bMin1[a];
                bMin1[a] = b;
            } else if (bMin2[a] > b) {
                bMin2[a] = b;
            }
        }

        int ib1 = n;
        int b2 = numeric_limits<int>::max();
        vector<long long> delCount(n + 1, 0);
        for (int i = n; i >= 1; i--) {
            if (bMin1[ib1] > bMin1[i]) {
                b2 = min(b2, bMin1[ib1]);
                ib1 = i;
            } else {
                b2 = min(b2, bMin1[i]);
            }
            retVal += (min(bMin1[ib1], n + 1) - i);
            delCount[ib1] += (min(min(b2, bMin2[ib1]), n + 1) - min(bMin1[ib1], n + 1));
        }
        retVal += *max_element(delCount.begin(), delCount.end());

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        vector<vector<int>> conflictingPairs;
    };
    vector<subject> testData{{4, {{2, 3}, {1, 4}}}, {5, {{1, 2}, {2, 5}, {3, 5}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 4, conflictingPairs = [[2,3],[1,4]]
     *  Output: 9
     *
     *  Input: n = 5, conflictingPairs = [[1,2],[2,5],[3,5]]
     *  Output: 12
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", conflictingPairs = [";
        for (long unsigned int j = 0; j < testData[i].conflictingPairs.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].conflictingPairs[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].conflictingPairs[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.maxSubarrays(testData[i].n, testData[i].conflictingPairs);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
