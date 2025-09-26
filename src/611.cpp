#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int triangleNumber(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();
        sort(nums.begin(), nums.end());
        for (int i = 0; i < numsSize; ++i) {
            int k = i;
            for (int j = i + 1; j < numsSize; ++j) {
                while ((k + 1 < numsSize) && (nums[k + 1] < nums[i] + nums[j])) {
                    ++k;
                }
                retVal += max(k - j, 0);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{2, 2, 3, 4}}, {{4, 2, 3, 4}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [2,2,3,4]
     *  Output: 3
     *
     *  Input: nums = [4,2,3,4]
     *  Output: 4
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.triangleNumber(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
