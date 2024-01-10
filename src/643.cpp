#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    double findMaxAverage(vector<int>& nums, int k) {
        double retVal;

        int numsSize = nums.size();

        double sum = 0;
        for (int i = 0; i < k; ++i) {
            sum += nums[i];
        }
        double maxValue = sum;

        for (int i = k; i < numsSize; ++i) {
            sum += (nums[i] - nums[i - k]);
            maxValue = max(maxValue, sum);
        }
        retVal = maxValue / k;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{1, 12, -5, -6, 50, 3}, 4}, {{5}, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,12,-5,-6,50,3], k = 4
     *  Output: 12.75000
     *
     *  Input: nums = [5], k = 1
     *  Output: 5.00000
     */

    Solution cSolution;
    double answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.findMaxAverage(testData[i].nums, testData[i].k);
        cout.setf(ios::fixed);
        cout.precision(5);

        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
