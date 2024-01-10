#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> singleNumber(vector<int>& nums) {
        vector<int> retVal(2, 0);

        unsigned int xorSum = 0;
        for (int num : nums) {
            xorSum ^= num;
        }
        unsigned int lsb = xorSum & (-xorSum);

        for (int num : nums) {
            retVal[((lsb & num) ? 1 : 0)] ^= num;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int target;
    };
    vector<subject> testData{{{1, 2, 1, 3, 2, 5}}, {{-1, 0}}, {{0, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2,1,3,2,5]
     *  Output: [3,5]
     *
     *  Input: nums = [-1,0]
     *  Output: [-1,0]
     *
     *  Input: nums = [0,1]
     *  Output: [1,0]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.singleNumber(testData[i].nums);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
