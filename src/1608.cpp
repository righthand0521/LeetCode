#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int specialArray(vector<int>& nums) {
        int retVal = -1;

        int numsSize = nums.size();
        vector<int> frequency(numsSize + 1, 0);
        for (int num : nums) {
            int index = min(numsSize, num);
            frequency[index] += 1;
        }

        int greaterThanOrEqual = 0;
        for (int i = numsSize; i >= 0; --i) {
            greaterThanOrEqual += frequency[i];
            if (i == greaterThanOrEqual) {
                retVal = i;
                break;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{3, 5}}, {{0, 0}}, {{0, 4, 3, 0, 4}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [3,5]
     *  Output: 2
     *
     *  Input: nums = [0,0]
     *  Output: -1
     *
     *  Input: nums = [0,4,3,0,4]
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

        answer = cSolution.specialArray(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
