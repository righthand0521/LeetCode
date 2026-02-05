#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> constructTransformedArray(vector<int>& nums) {
        vector<int> retVal;

        int numsSize = nums.size();

        for (int i = 0; i < numsSize; ++i) {
            int index = ((i + nums[i]) % numsSize + numsSize) % numsSize;
            retVal.push_back(nums[index]);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{3, -2, 1, 1}}, {{-1, 4, -1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [3,-2,1,1]
     *  Output: [1,1,1,3]
     *
     *  Input: nums = [-1,4,-1]
     *  Output: [-1,-1,4]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.constructTransformedArray(testData[i].nums);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
