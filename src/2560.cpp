#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minCapability(vector<int>& nums, int k) {
        int retVal = 0;

        int totalHouses = nums.size();
        int left = 1;
        int right = *max_element(nums.begin(), nums.end());
        while (left < right) {
            int middle = (left + right) / 2;
            int possibleThefts = 0;

            for (int index = 0; index < totalHouses; ++index) {
                if (nums[index] <= middle) {
                    possibleThefts += 1;
                    index++;  // Skip the next house to maintain the non-adjacent condition
                }
            }

            if (possibleThefts >= k) {
                right = middle;
            } else {
                left = middle + 1;
            }
        }
        retVal = left;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{2, 3, 5, 9}, 2}, {{2, 7, 9, 3, 1}, 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [2,3,5,9], k = 2
     *  Output: 5
     *
     *  Input: nums = [2,7,9,3,1], k = 2
     *  Output: 2
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.minCapability(testData[i].nums, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
