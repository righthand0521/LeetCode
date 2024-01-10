#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int arraySign(vector<int>& nums) {
        int retVal = 1;

        for (long unsigned int i = 0; i < nums.size(); ++i) {
            if (nums[i] == 0) {
                retVal = 0;
                break;
            } else if (nums[i] > 0) {
                retVal *= 1;
            } else if (nums[i] < 0) {
                retVal *= (-1);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{-1, -2, -3, -4, 3, 2, 1}}, {{1, 5, 0, 2, -3}}, {{-1, 1, -1, 1, -1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [-1,-2,-3,-4,3,2,1]
     *  Output: 1
     *
     *  Input: nums = [1,5,0,2,-3]
     *  Output: 0
     *
     *  Input: nums = [-1,1,-1,1,-1]
     *  Output: -1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.arraySign(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
