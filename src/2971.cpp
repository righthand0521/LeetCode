#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    long long largestPerimeter(vector<int>& nums) {
        long long retVal = -1;

        int numsSize = nums.size();

        sort(nums.begin(), nums.end());
        long long sum = nums[0] + nums[1];
        for (int i = 2; i < numsSize; ++i) {
            if (sum > nums[i]) {
                retVal = sum + nums[i];
            }
            sum += nums[i];
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{5, 5, 5}}, {{1, 12, 1, 2, 5, 50, 3}}, {{5, 5, 50}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [5,5,5]
     *  Output: 15
     *
     *  Input: nums = [1,12,1,2,5,50,3]
     *  Output: 12
     *
     *  Input: nums = [5,5,50]
     *  Output: -1
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.largestPerimeter(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
