#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxProduct(vector<int>& nums) {
        int retVal = 0;

        sort(nums.begin(), nums.end(), greater());
        int first = nums[0] - 1;
        int second = nums[1] - 1;
        retVal = first * second;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{3, 4, 5, 2}}, {{1, 5, 4, 5}}, {{3, 7}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [3,4,5,2]
     *  Output: 12
     *
     *  Input: nums = [1,5,4,5]
     *  Output: 16
     *
     *  Input: nums = [3,7]
     *  Output: 12
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.maxProduct(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
