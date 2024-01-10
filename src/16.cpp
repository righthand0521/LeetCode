#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   public:
    int threeSumClosest(vector<int>& nums, int target) {
        int retVal = 0;

        sort(nums.begin(), nums.end());

        int closest = numeric_limits<int>::max();
        int numsSize = nums.size();
        for (int first = 0; first < numsSize - 2; ++first) {
            int second = first + 1;
            int third = numsSize - 1;
            while (second < third) {
                int sum = nums[first] + nums[second] + nums[third];
                int diff = abs(target - sum);
                if (closest > diff) {
                    closest = diff;
                    retVal = sum;
                }

                if (sum == target) {
                    return retVal;
                } else if (sum < target) {
                    second += 1;
                } else if (sum > target) {
                    third -= 1;
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int target;
    };
    vector<subject> testData{{{-1, 2, 1, -4}, 1}, {{0, 0, 0}, 1}, {{4, 0, 5, -5, 3, 3, 0, -4, -5}, -2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [-1,2,1,-4], target = 1
     *  Output: 2
     *
     *  Input: nums = [0,0,0], target = 1
     *  Output: 0
     *
     *  Input: nums = [4,0,5,-5,3,3,0,-4,-5], target = -2
     *  Output: -2
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], target = " << testData[i].target << "\n";

        answer = cSolution.threeSumClosest(testData[i].nums, testData[i].target);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
