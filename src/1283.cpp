#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int smallestDivisor(vector<int>& nums, int threshold) {
        int retVal = 0;

        int left = 1;
        int right = *max_element(nums.begin(), nums.end());
        while (left < right) {
            int middle = left + (right - left) / 2;

            int sum = 0;
            for (auto num : nums) {
                sum += ((num + middle - 1) / middle);
            }

            if (sum > threshold) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }
        retVal = left;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int threshold;
    };
    vector<subject> testData{{{1, 2, 5, 9}, 6}, {{44, 22, 33, 11, 1}, 5}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2,5,9], threshold = 6
     *  Output: 5
     *
     *  Input: nums = [44,22,33,11,1], threshold = 5
     *  Output: 44
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], threshold = " << testData[i].threshold << "\n";

        answer = cSolution.smallestDivisor(testData[i].nums, testData[i].threshold);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
