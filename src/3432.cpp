#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int countPartitions(vector<int>& nums) {
        int retVal = 0;

        int sumNums = 0;
        for (int num : nums) {
            sumNums += num;
        }
        if (sumNums % 2 == 0) {
            retVal = nums.size() - 1;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{10, 10, 3, 7, 6}}, {{1, 2, 2}}, {{2, 4, 6, 8}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [10,10,3,7,6]
     *  Output: 4
     *
     *  Input: nums = [1,2,2]
     *  Output: 0
     *
     *  Input: nums = [2,4,6,8]
     *  Output: 3
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.countPartitions(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
