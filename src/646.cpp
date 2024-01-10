#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
#define GREEDY (1)
#define DYNAMIC_PROGRAMMING (1)
   public:
    Solution() {
#if (GREEDY)
        cout << "Greedy\n\n";
#elif (DYNAMIC_PROGRAMMING)
        cout << "Dynamic Programming\n\n";
#endif
    }
    int findLongestChain(vector<vector<int>>& pairs) {
        int retVal = 0;

#if (GREEDY)
        sort(pairs.begin(), pairs.end(), [&](const vector<int>& x, const vector<int>& y) {
            // ascending order
            if (x[1] == y[1]) {
                return (x[0] < y[0]);
            }
            return (x[1] < y[1]);
        });

        int preRight = -1001;  // -1000 <= lefti < righti <= 1000
        for (auto pair : pairs) {
            int left = pair[0];
            int right = pair[1];

            if (left > preRight) {
                ++retVal;
                preRight = right;
            }
        }
#elif (DYNAMIC_PROGRAMMING)
        sort(pairs.begin(), pairs.end());

        // dp[i] will store the length of the longest chain starting from pair i
        int pairsSize = pairs.size();
        vector<int> dp(pairsSize, 1);
        for (int i = pairsSize - 1; i >= 0; --i) {
            int preRight = pairs[i][1];
            for (int j = i + 1; j < pairsSize; ++j) {
                int left = pairs[j][0];
                if (preRight < left) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            retVal = max(retVal, dp[i]);
        }
#endif

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> pairs;
    };
    vector<subject> testData{{{{1, 2}, {2, 3}, {3, 4}}},
                             {{{1, 2}, {7, 8}, {4, 5}}},
                             {{{1, 2}, {2, 5}, {3, 9}, {6, 7}, {8, 9}}},
                             {{{7, 9}, {4, 5}, {7, 9}, {-7, -1}, {0, 10}, {3, 10}, {3, 6}, {2, 3}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: pairs = [[1,2],[2,3],[3,4]]
     *  Output: 2
     *
     *  Input: pairs = [[1,2],[7,8],[4,5]]
     *  Output: 3
     *
     *  Input: pairs = [[1,2],[2,5],[3,9],[6,7],[8,9]]
     *  Output: 3
     *
     *  Input: pairs = [[7,9],[4,5],[7,9],[-7,-1],[0,10],[3,10],[3,6],[2,3]]
     *  Output: 4
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: pairs = [";
        for (long unsigned int j = 0; j < testData[i].pairs.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].pairs[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].pairs[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.findLongestChain(testData[i].pairs);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
