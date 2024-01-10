#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> retVal;

        int numsSize = nums.size();
        if (numsSize < 3) {
            return retVal;
        }

        sort(nums.begin(), nums.end());
        for (int first = 0; first < numsSize - 2; ++first) {
            if (nums[first] > 0) {
                break;
            }

            // Notice that the order of the output and the order of the triplets does not matter.
            if ((first > 0) && (nums[first - 1] == nums[first])) {
                continue;
            }

            int second = first + 1;
            int third = numsSize - 1;
            while (second < third) {
                int target = nums[first] + nums[second] + nums[third];
                if (target == 0) {
                    // Notice that the order of the output and the order of the triplets does not matter.
                    if ((second > first + 1) && (nums[second - 1] == nums[second])) {
                        second += 1;
                        continue;
                    }
                    vector<int> tmp = {nums[first], nums[second], nums[third]};
                    retVal.emplace_back(tmp);
                    second += 1;
                    third -= 1;
                } else if (target < 0) {
                    second += 1;
                } else if (target > 0) {
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
    };
    vector<subject> testData{{{-1, 0, 1, 2, -1, -4}}, {{0, 1, 1}}, {{0, 0, 0}}, {{-2, 0, 1, 1, 2}}, {{-2, 0, 0, 2, 2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [-1,0,1,2,-1,-4]
     *  Output: [[-1,-1,2],[-1,0,1]]
     *
     *  Input: nums = [0,1,1]
     *  Output: []
     *
     *  Input: nums = [0,0,0]
     *  Output: [[0,0,0]]
     *
     *  Input: nums = [-2,0,1,1,2]
     *  Output: [[-2,0,2],[-2,1,1]]
     *
     *  Input: nums = [-2,0,0,2,2]
     *  Output: [[-2,0,2]]
     */

    Solution cSolution;
    vector<vector<int>> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.threeSum(testData[i].nums);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < answer[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << answer[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
