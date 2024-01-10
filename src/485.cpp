#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int retVal = 0;

        int count = 0;
        for (int num : nums) {
            if (num == 1) {
                ++count;
            } else {
                retVal = max(retVal, count);
                count = 0;
            }
        }
        retVal = max(retVal, count);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 1, 0, 1, 1, 1}}, {{1, 0, 1, 1, 0, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,1,0,1,1,1]
     *  Output: 3
     *
     *  Input: nums = [1,0,1,1,0,1]
     *  Output: 2
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.findMaxConsecutiveOnes(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
