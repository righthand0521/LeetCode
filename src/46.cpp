#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    void backtracking(vector<vector<int>>& answer, vector<int>& output, int first, int len) {
        if (first == len) {
            answer.emplace_back(output);
            return;
        }

        for (int i = first; i < len; ++i) {
            swap(output[i], output[first]);
            backtracking(answer, output, first + 1, len);
            swap(output[i], output[first]);
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> retVal;

        int numsSize = nums.size();
        backtracking(retVal, nums, 0, numsSize);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 2, 3}}, {{0, 1}}, {{1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2,3]
     *  Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
     *
     *  Input: nums = [0,1]
     *  Output: [[0,1],[1,0]]
     *
     *  Input: nums = [1]
     *  Output: [[1]]
     */

    Solution cSolution;
    vector<vector<int>> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.permute(testData[i].nums);
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
