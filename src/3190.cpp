#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minimumOperations(vector<int>& nums) {
        int retVal = 0;

        for (int num : nums) {
            int remainder = num % 3;
            int multiple = 3 - remainder;
            retVal += min(remainder, multiple);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 2, 3, 4}}, {{3, 6, 9}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2,3,4]
     *  Output: 3
     *
     *  Input: nums = [3,6,9]
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

        answer = cSolution.minimumOperations(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
