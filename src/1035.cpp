#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
        int retVal = 0;

        int len1 = nums1.size();
        int len2 = nums2.size();

        /* Example: Input: nums1 = [2,5,1,2,5], nums2 = [10,5,2,1,5,2]
         *     10 5 2 1 5 2
         *    0 0 0 0 0 0 0
         *  2 0 0 0 1 1 1 1
         *  5 0 0 1 1 1 2 2
         *  1 0 0 1 1 2 2 2
         *  2 0 0 1 2 2 2 3
         *  5 0 0 1 2 2 3 3
         */
        vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1));
        int idx1, idx2;
        for (idx1 = 1; idx1 <= len1; ++idx1) {
            for (idx2 = 1; idx2 <= len2; ++idx2) {
                if (nums1[idx1 - 1] == nums2[idx2 - 1]) {
                    dp[idx1][idx2] = dp[idx1 - 1][idx2 - 1] + 1;
                } else {
                    dp[idx1][idx2] = max(dp[idx1 - 1][idx2], dp[idx1][idx2 - 1]);
                }
            }
        }
        retVal = dp[len1][len2];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums1;
        vector<int> nums2;
    };
    vector<subject> testData{
        {{1, 4, 2}, {1, 2, 4}}, {{2, 5, 1, 2, 5}, {10, 5, 2, 1, 5, 2}}, {{1, 3, 7, 1, 7, 5}, {1, 9, 2, 5, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums1 = [1,4,2], nums2 = [1,2,4]
     *  Output: 2
     *
     *  Input: nums1 = [2,5,1,2,5], nums2 = [10,5,2,1,5,2]
     *  Output: 3
     *
     *  Input: nums1 = [1,3,7,1,7,5], nums2 = [1,9,2,5,1]
     *  Output: 2
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

        answer = cSolution.maxUncrossedLines(testData[i].nums1, testData[i].nums2);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
