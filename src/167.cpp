#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int> retVal;

        int left = 0;
        int right = numbers.size() - 1;
        int sum = numbers[left] + numbers[right];
        while (sum != target) {
            if (sum > target) {
                --right;
            } else if (sum < target) {
                ++left;
            }
            sum = numbers[left] + numbers[right];
        }
        retVal.emplace_back(left + 1);
        retVal.emplace_back(right + 1);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int target;
    };
    vector<subject> testData{{{2, 7, 11, 15}, 9}, {{2, 3, 4}, 6}, {{-1, 0}, -1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [2,7,11,15], target = 9
     *  Output: [1,2]
     *
     *  Input: numbers = [2,3,4], target = 6
     *  Output: [1,3]
     *
     *  Input: nums = [-1,0], target = -1
     *  Output: [1,2]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], target = " << testData[i].target << "\n";

        answer = cSolution.twoSum(testData[i].nums, testData[i].target);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
