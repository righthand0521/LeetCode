#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int findMaxK(vector<int>& nums) {
        int retVal = -1;

        sort(nums.begin(), nums.end());

        int left = 0;
        int right = nums.size() - 1;
        while (left < right) {
            if ((-nums[left]) == nums[right]) {
                retVal = nums[right];
                break;
            } else if ((-nums[left]) > nums[right]) {
                left += 1;
            } else if ((-nums[left]) < nums[right]) {
                right -= 1;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{-1, 2, -3, 3}}, {{-1, 10, 6, 7, -7, 1}}, {{-10, 8, 6, 7, -2, -3}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [-1,2,-3,3]
     *  Output: 3
     *
     *  Input: nums = [-1,10,6,7,-7,1]
     *  Output: 7
     *
     *  Input: nums = [-10,8,6,7,-2,-3]
     *  Output: -1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.findMaxK(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
