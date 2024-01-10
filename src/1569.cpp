#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
#define MODULO (int)(1e9 + 7)
   private:
    long long dfs(vector<int>& nums, vector<vector<long long>>& table) {
        int retVal = 1;

        int numsSize = nums.size();
        if (numsSize < 3) {
            return retVal;
        }

        vector<int> leftNodes;
        vector<int> rightNodes;
        for (int i = 1; i < numsSize; ++i) {
            if (nums[i] < nums[0]) {
                leftNodes.push_back(nums[i]);
            } else {
                rightNodes.push_back(nums[i]);
            }
        }

        long long leftWays = dfs(leftNodes, table) % MODULO;
        long long rightWays = dfs(rightNodes, table) % MODULO;
        retVal = (((leftWays * rightWays) % MODULO) * table[numsSize - 1][leftNodes.size()]) % MODULO;

        return retVal;
    }

   public:
    int numOfWays(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();
        vector<vector<long long>> table(numsSize + 1);
        for (int i = 0; i < numsSize + 1; ++i) {
            table[i] = vector<long long>(i + 1, 1);
            for (int j = 1; j < i; ++j) {
                table[i][j] = (table[i - 1][j - 1] + table[i - 1][j]) % MODULO;
            }
        }
        retVal = (dfs(nums, table) - 1) % MODULO;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{2, 1, 3}}, {{3, 4, 5, 1, 2}}, {{1, 2, 3}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [2,1,3]
     *  Output: 1
     *
     *  Input: nums = [3,4,5,1,2]
     *  Output: 5
     *
     *  Input: nums = [1,2,3]
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.numOfWays(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
