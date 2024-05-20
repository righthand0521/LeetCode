#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> retVal;

        int numsSize = nums.size();
        for (int bitmask = 0; bitmask < (1 << numsSize); ++bitmask) {
            vector<int> sequence;
            for (int i = 0; i < numsSize; ++i) {
                if (((bitmask >> i) & 1) == 1) {
                    sequence.push_back(nums[i]);
                }
            }
            retVal.push_back(sequence);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 2, 3}}, {{0}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2,3]
     *  Output: [[], [1], [2], [1, 2], [3], [1, 3], [2, 3], [1, 2, 3]]
     *
     *  Input: nums = [0]
     *  Output: [[], [0]]
     */

    Solution cSolution;
    vector<vector<int>> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.subsets(testData[i].nums);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < answer[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << answer[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
