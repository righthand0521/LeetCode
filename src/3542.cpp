#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minOperations(vector<int>& nums) {
        int retVal = 0;

        vector<int> monotonicStack;
        for (int num : nums) {
            while ((monotonicStack.empty() == false) && (monotonicStack.back() > num)) {
                monotonicStack.pop_back();
            }
            if (num == 0) {
                continue;
            }

            if ((monotonicStack.empty() == true) || (monotonicStack.back() < num)) {
                ++retVal;
                monotonicStack.push_back(num);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{0, 2}}, {{3, 1, 2, 1}}, {{1, 2, 1, 2, 1, 2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [0,2]
     *  Output: 1
     *
     *  Input: nums = [3,1,2,1]
     *  Output: 3
     *
     *  Input: nums = [1,2,1,2,1,2]
     *  Output: 4
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.minOperations(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
