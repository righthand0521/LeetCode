#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   public:
    int minOperations(vector<int>& nums, int k) {
        int retVal = -1;  // If it is impossible to make all elements equal to k, return -1.

        unordered_set<int> hashTable;
        for (int x : nums) {
            if (x < k) {
                return retVal;
            } else if (x > k) {
                hashTable.insert(x);
            }
        }
        retVal = hashTable.size();

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{5, 2, 5, 4, 5}, 2}, {{2, 1, 2}, 2}, {{9, 7, 5, 3}, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [5,2,5,4,5], k = 2
     *  Output: 2
     *
     *  Input: nums = [2,1,2], k = 2
     *  Output: -1
     *
     *  Input: nums = [9,7,5,3], k = 1
     *  Output: 4
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.minOperations(testData[i].nums, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
