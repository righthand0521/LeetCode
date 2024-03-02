#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> sortedSquares(vector<int>& nums) {
        vector<int> retVal;

        int numsSize = nums.size();
        retVal.resize(numsSize, 0);

        int left = 0;
        int right = numsSize - 1;
        for (int i = (numsSize - 1); i >= 0; --i) {
            if (abs(nums[left]) > abs(nums[right])) {
                retVal[i] = nums[left] * nums[left];
                ++left;
            } else {
                retVal[i] = nums[right] * nums[right];
                --right;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{-4, -1, 0, 3, 10}}, {{-7, -3, 2, 3, 11}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [-4,-1,0,3,10]
     *  Output: [0,1,9,16,100]
     *
     *  Input: nums = [-7,-3,2,3,11]
     *  Output: [4,9,9,49,121]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.sortedSquares(testData[i].nums);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
