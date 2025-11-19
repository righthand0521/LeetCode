#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   public:
    int findFinalValue(vector<int>& nums, int original) {
        int retVal = 0;

        unordered_set<int> hashTable(nums.begin(), nums.end());
        while (hashTable.count(original)) {
            original *= 2;
        }
        retVal = original;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int original;
    };
    vector<subject> testData{{{5, 3, 6, 1, 12}, 3}, {{2, 7, 9}, 4}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [5,3,6,1,12], original = 3
     *  Output: 24
     *
     *  Input: nums = [2,7,9], original = 4
     *  Output: 4
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], original = " << testData[i].original << "\n";

        answer = cSolution.findFinalValue(testData[i].nums, testData[i].original);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
