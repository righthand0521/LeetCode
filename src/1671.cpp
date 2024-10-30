#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> getLongestIncreasingSubsequenceLength(vector<int>& v) {
        vector<int> retVal;

        int vSize = v.size();
        retVal.resize(vSize, 1);

        vector<int> lis = {v[0]};
        for (int i = 1; i < vSize; i++) {
            int index = lower_bound(lis.begin(), lis.end(), v[i]) - lis.begin();
            int lisSize = lis.size();
            if (index == lisSize) {
                lis.push_back(v[i]);
            } else {
                lis[index] = v[i];
            }

            retVal[i] = lis.size();
        }

        return retVal;
    }
    int minimumMountainRemovals(vector<int>& nums) {
        int retVal = 0;

        vector<int> lisLength = getLongestIncreasingSubsequenceLength(nums);
        reverse(nums.begin(), nums.end());
        vector<int> ldsLength = getLongestIncreasingSubsequenceLength(nums);
        reverse(ldsLength.begin(), ldsLength.end());

        int numsSize = nums.size();
        retVal = numeric_limits<int>::max();
        for (int i = 0; i < numsSize; i++) {
            if ((lisLength[i] > 1) && (ldsLength[i] > 1)) {
                retVal = min(retVal, numsSize - lisLength[i] - ldsLength[i] + 1);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 3, 1}}, {{2, 1, 1, 5, 6, 2, 3, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,3,1]
     *  Output: 0
     *
     *  Input: nums = [2,1,1,5,6,2,3,1]
     *  Output: 3
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.minimumMountainRemovals(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
