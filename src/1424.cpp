#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> findDiagonalOrder(vector<vector<int>>& nums) {
        vector<int> retVal;

        int numsSize = nums.size();

        queue<pair<int, int>> queue;
        queue.push({0, 0});
        while (queue.empty() == false) {
            auto [row, col] = queue.front();
            queue.pop();
            retVal.emplace_back(nums[row][col]);

            if ((col == 0) && (row + 1 < numsSize)) {
                queue.push({row + 1, col});
            }

            int numsColSize = nums[row].size();
            if (col + 1 < numsColSize) {
                queue.push({row, col + 1});
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> nums;
    };
    vector<subject> testData{{{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}},
                             {{{1, 2, 3, 4, 5}, {6, 7}, {8}, {9, 10, 11}, {12, 13, 14, 15, 16}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [[1,2,3],[4,5,6],[7,8,9]]
     *  Output: [1,4,2,7,5,3,8,6,9]
     *
     *  Input: nums = [[1,2,3,4,5],[6,7],[8],[9,10,11],[12,13,14,15,16]]
     *  Output: [1,6,2,8,7,3,9,4,12,10,5,13,11,14,15,16]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].nums[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].nums[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.findDiagonalOrder(testData[i].nums);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
