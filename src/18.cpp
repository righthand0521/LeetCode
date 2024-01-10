#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> retVal;

        int numsSize = nums.size();
        if (numsSize < 4) {
            return retVal;
        }

        sort(nums.begin(), nums.end());
        for (int a = 0; a < numsSize - 3; ++a) {
            // Notice that the order of the output and the order of the triplets does not matter.
            if ((a > 0) && (nums[a - 1] == nums[a])) {
                continue;
            }

            for (int b = a + 1; b < numsSize - 2; ++b) {
                // Notice that the order of the output and the order of the triplets does not matter.
                if ((b > a + 1) && (nums[b - 1] == nums[b])) {
                    continue;
                }

                int c = b + 1;
                int d = numsSize - 1;
                while (c < d) {
                    long compare = (long)(nums[a]) + (long)(nums[b]) + (long)(nums[c]) + (long)(nums[d]);
                    if (compare < target) {
                        c += 1;
                    } else if (compare > target) {
                        d -= 1;
                    } else {
                        // Notice that the order of the output and the order of the triplets does not matter.
                        if ((c > b + 1) && (nums[c - 1] == nums[c])) {
                            c += 1;
                            continue;
                        }

                        vector<int> tmp = {nums[a], nums[b], nums[c], nums[d]};
                        retVal.emplace_back(tmp);
                        c += 1;
                        d -= 1;
                    }
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
    vector<subject> testData{
        {{1, 0, -1, 0, -2, 2}, 0}, {{2, 2, 2, 2, 2}, 8}, {{1000000000, 1000000000, 1000000000, 1000000000}, 0}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,0,-1,0,-2,2], target = 0
     *  Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
     *
     *  Input: nums = [2,2,2,2,2], target = 8
     *  Output: [[2,2,2,2]]
     *
     *  Input: nums = [1000000000,1000000000,1000000000,1000000000], target = 0
     *  Output: []
     */

    Solution cSolution;
    vector<vector<int>> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], target = " << testData[i].target << "\n";

        answer = cSolution.fourSum(testData[i].nums, testData[i].target);
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
