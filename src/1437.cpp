#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool kLengthApart(vector<int>& nums, int k) {
        bool retVal = false;

        int numsSize = nums.size();
        int previous = -1;
        for (int i = 0; i < numsSize; ++i) {
            if (nums[i] != 1) {
                continue;
            }
            if ((previous != -1) && (i - previous - 1 < k)) {
                return retVal;
            }
            previous = i;
        }
        retVal = true;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{1, 0, 0, 0, 1, 0, 0, 1}, 2}, {{1, 0, 0, 1, 0, 1}, 2}};
    int numberOfTestCase = testData.size();
    /* Example:
     *  Input: nums = [1,0,0,0,1,0,0,1], k = 2
     *  Output: true
     *
     *  Input: nums = [1,0,0,1,0,1], k = 2
     *  Output: false
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.kLengthApart(testData[i].nums, testData[i].k);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
