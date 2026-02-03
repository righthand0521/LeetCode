#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool isTrionic(vector<int>& nums) {
        bool retVal = false;

        int numsSize = nums.size();
        int i = 1;

        while ((i < numsSize) && (nums[i - 1] < nums[i])) {
            i += 1;
        }
        int p = i - 1;
        if (p == 0) {
            return retVal;
        }

        while ((i < numsSize) && (nums[i - 1] > nums[i])) {
            i += 1;
        }
        int q = i - 1;
        if (q == p) {
            return retVal;
        }

        while ((i < numsSize) && (nums[i - 1] < nums[i])) {
            i += 1;
        }
        i -= 1;
        if (i != (numsSize - 1)) {
            return retVal;
        } else if (i == q) {
            return retVal;
        } else {
            retVal = true;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 3, 5, 4, 2, 6}}, {{2, 1, 3}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,3,5,4,2,6]
     *  Output: true
     *
     *  Input: nums = [2,1,3]
     *  Output: false
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.isTrionic(testData[i].nums);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
