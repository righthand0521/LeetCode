#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int countValidSelections(vector<int>& nums) {
        int retVal = 0;

        int left = 0;
        int right = 0;
        for (int num : nums) {
            right += num;
        }

        for (int num : nums) {
            if (num == 0) {
                if ((left - right >= 0) && (left - right <= 1)) {
                    retVal++;
                }
                if ((right - left) >= 0 && (right - left <= 1)) {
                    retVal++;
                }
            } else {
                left += num;
                right -= num;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 0, 2, 0, 3}}, {{2, 3, 4, 0, 4, 1, 0}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,0,2,0,3]
     *  Output: 2
     *
     *  Input: nums = [2,3,4,0,4,1,0]
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.countValidSelections(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
