#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    long long maximumValueSum(vector<int>& nums, int k, vector<vector<int>>& edges) {
        long long retVal = 0;

        long long sum = 0;
        int count = 0;
        int positiveMinimum = (1 << 30);
        int negativeMaximum = -1 * (1 << 30);
        for (int nodeValue : nums) {
            int operatedNodeValue = nodeValue ^ k;
            sum += nodeValue;
            int netChange = operatedNodeValue - nodeValue;
            if (netChange > 0) {
                positiveMinimum = min(positiveMinimum, netChange);
                sum += netChange;
                count++;
            } else {
                negativeMaximum = max(negativeMaximum, netChange);
            }
        }

        // If the number of positive netChange values is even return the sum.
        // Otherwise return the maximum of both discussed cases.
        if (count % 2 == 0) {
            retVal = sum;
        } else {
            retVal = max(sum - positiveMinimum, sum + negativeMaximum);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
        vector<vector<int>> edges;
    };
    vector<subject> testData{{{1, 2, 1}, 3, {{0, 1}, {0, 2}}},
                             {{2, 3}, 7, {{0, 1}}},
                             {{7, 7, 7, 7, 7, 7}, 3, {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2,1], k = 3, edges = [[0,1],[0,2]]
     *  Output: 6
     *
     *  Input: nums = [2,3], k = 7, edges = [[0,1]]
     *  Output: 9
     *
     *  Input: nums = [7,7,7,7,7,7], k = 3, edges = [[0,1],[0,2],[0,3],[0,4],[0,5]]
     *  Output: 42
     */

    Solution cSolution;
    long long answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << ", edges = [";
        for (long unsigned int j = 0; j < testData[i].edges.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].edges[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].edges[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.maximumValueSum(testData[i].nums, testData[i].k, testData[i].edges);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
