#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

class Solution {
   public:
    int minOperations(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();

        set<int> unique(nums.begin(), nums.end());
        vector<int> numsUiqueSort;
        for (int num : unique) {
            numsUiqueSort.push_back(num);
        }
        int numsUiqueSortSize = numsUiqueSort.size();

        retVal = numsSize;
        int j = 0;
        for (int i = 0; i < numsUiqueSortSize; i++) {
            while ((j < numsUiqueSortSize) && (numsUiqueSort[j] < numsUiqueSort[i] + numsSize)) {
                j++;
            }

            int count = j - i;
            retVal = min(retVal, numsSize - count);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{4, 2, 5, 3}}, {{1, 2, 3, 5, 6}}, {{1, 10, 100, 1000}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [4,2,5,3]
     *  Output: 0
     *
     *  Input: nums = [1,2,3,5,6]
     *  Output: 1
     *
     *  Input: nums = [1,10,100,1000]
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

        answer = cSolution.minOperations(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
