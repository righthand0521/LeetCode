#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> buildArray(vector<int>& nums) {
        vector<int> retVal;

        int numsSize = nums.size();
        for (int i = 0; i < numsSize; ++i) {
            retVal.emplace_back(nums[nums[i]]);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{0, 2, 1, 5, 3, 4}}, {{5, 0, 1, 2, 3, 4}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [0,2,1,5,3,4]
     *  Output: [0,1,2,4,5,3]
     *
     *  Input: nums = [5,0,1,2,3,4]
     *  Output: [4,5,0,1,2,3]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.buildArray(testData[i].nums);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
