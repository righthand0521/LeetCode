#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int findMin(vector<int>& nums) {
        int retVal = 0;

        int left = 0;
        int right = nums.size() - 1;
        while (left < right) {
            int middle = left + (right - left) / 2;
            if (nums[middle] < nums[right]) {
                right = middle;
            } else {
                left = middle + 1;
            }
        }
        retVal = nums[left];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{3, 4, 5, 1, 2}}, {{4, 5, 6, 7, 0, 1, 2}}, {{11, 13, 15, 17}}, {{2, 1}}, {{2, 3, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [3,4,5,1,2]
     *  Output: 1
     *
     *  Input: nums = [4,5,6,7,0,1,2]
     *  Output: 0
     *
     *  Input: nums = [11,13,15,17]
     *  Output: 11
     *
     *  Input: nums = [2,1]
     *  Output: 1
     *
     *  Input: nums = [2,3,1]
     *  Output: 1
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.findMin(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
