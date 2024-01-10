#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
        int retVal = 0;

        int nums1Size = nums1.size();
        int nums2Size = nums2.size();
        vector<vector<int>> dp(nums1Size, vector<int>(nums2Size, 0));
        for (int row = 0; row < nums1Size; ++row) {
            for (int col = 0; col < nums2Size; ++col) {
                int product = nums1[row] * nums2[col];

                dp[row][col] = product;
                if (row > 0) {
                    dp[row][col] = max(dp[row][col], dp[row - 1][col]);
                }
                if (col > 0) {
                    dp[row][col] = max(dp[row][col], dp[row][col - 1]);
                }
                if ((row > 0) && (col > 0)) {
                    dp[row][col] = max(dp[row][col], dp[row - 1][col - 1] + product);
                }
            }
        }
        retVal = dp[nums1Size - 1][nums2Size - 1];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums1;
        vector<int> nums2;
    };
    vector<subject> testData{{{2, 1, -2, 5}, {3, 0, -6}}, {{3, -2}, {2, -6, 7}}, {{-1, -1}, {1, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums1 = [2,1,-2,5], nums2 = [3,0,-6]
     *  Output: 18
     *
     *  Input: nums1 = [3,-2], nums2 = [2,-6,7]
     *  Output: 21
     *
     *  Input: nums1 = [-1,-1], nums2 = [1,1]
     *  Output: -1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums1 = [";
        for (long unsigned int j = 0; j < testData[i].nums1.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums1[j];
        }
        cout << "], nums2 = [";
        for (long unsigned int j = 0; j < testData[i].nums2.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums2[j];
        }
        cout << "]\n";

        answer = cSolution.maxDotProduct(testData[i].nums1, testData[i].nums2);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
