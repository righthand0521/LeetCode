#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<int>> divideArray(vector<int>& nums, int k) {
        vector<vector<int>> retVal;

        int numsSize = nums.size();
        if (numsSize % 3 != 0) {
            return retVal;
        }

        sort(nums.begin(), nums.end());
        for (int i = 0; i < numsSize; i += 3) {
            if (nums[i + 2] - nums[i] > k) {
                retVal = {};
                break;
            }

            retVal.push_back({nums[i], nums[i + 1], nums[i + 2]});
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{1, 3, 4, 8, 7, 9, 3, 5, 1}, 2},
                             {{1, 3, 3, 2, 7, 3}, 3},
                             {{15, 13, 12, 13, 12, 14, 12, 2, 3, 13, 12, 14, 14, 13, 5, 12, 12, 2, 13, 2, 2}, 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,3,4,8,7,9,3,5,1], k = 2
     *  Output: [[1,1,3],[3,4,5],[7,8,9]]
     *
     *  Input: nums = [1,3,3,2,7,3], k = 3
     *  Output: []
     *
     *  Input: nums = [15,13,12,13,12,14,12,2,3,13,12,14,14,13,5,12,12,2,13,2,2], k = 2
     *  Output: []
     */

    Solution cSolution;
    vector<vector<int>> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.divideArray(testData[i].nums, testData[i].k);
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
