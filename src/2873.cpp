#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    long long maximumTripletValue(vector<int>& nums) {
        long long retVal = 0;

        int numsSize = nums.size();
        long long idxMax = 0;
        long long diffMax = 0;
        for (int k = 0; k < numsSize; k++) {
            retVal = max(retVal, diffMax * nums[k]);
            diffMax = max(diffMax, idxMax - nums[k]);
            idxMax = max(idxMax, (long long)nums[k]);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{12, 6, 1, 2, 7}}, {{1, 10, 3, 4, 19}}, {{1, 2, 3}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [12,6,1,2,7]
     *  Output: 77
     *
     *  Input: nums = [1,10,3,4,19]
     *  Output: 133
     *
     *  Input: nums = [1,2,3]
     *  Output: 0
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.maximumTripletValue(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
