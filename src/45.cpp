#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int jump(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();
        int maxPosition = 0;
        int end = 0;
        for (int i = 0; i < (numsSize - 1); ++i) {
            // find maximum jumping length
            maxPosition = max(maxPosition, nums[i] + i);

            // reach end boundary need to  update end boundary and add steps
            if (i == end) {
                end = maxPosition;
                ++retVal;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{2, 3, 1, 1, 4}}, {{2, 3, 0, 1, 4}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [2,3,1,1,4]
     *  Output: 2
     *
     *  Input: nums = [2,3,0,1,4]
     *  Output: 2
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.jump(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
