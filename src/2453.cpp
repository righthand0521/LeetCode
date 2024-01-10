#include <algorithm>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int destroyTargets(vector<int>& nums, int space) {
        int retVal = numeric_limits<int>::max();

        int maxTarget = 0;
        unordered_map<int, int> count;
        for (auto num : nums) {
            count[num % space] += 1;
            maxTarget = max(maxTarget, count[num % space]);
        }

        for (auto num : nums) {
            if (count[num % space] == maxTarget) {
                retVal = min(retVal, num);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int space;
    };
    vector<subject> testData{{{3, 7, 8, 1, 1, 5}, 2}, {{1, 3, 5, 2, 4, 6}, 2}, {{6, 2, 5}, 100}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [3,7,8,1,1,5], space = 2
     *  Output: 1
     *
     *  Input: nums = [1,3,5,2,4,6], space = 2
     *  Output: 1
     *
     *  Input: nums = [6,2,5], space = 100
     *  Output: 2
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "], space = " << testData[i].space << "\n";

        answer = cSolution.destroyTargets(testData[i].nums, testData[i].space);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
