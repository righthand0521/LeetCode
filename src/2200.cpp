#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> findKDistantIndices(vector<int>& nums, int key, int k) {
        vector<int> retVal;

        int numsSize = nums.size();

        int left = 0;
        int right = 0;
        for (int j = 0; j < numsSize; ++j) {
            if (nums[j] != key) {
                continue;
            }

            right = max(left, j - k);
            left = min(numsSize - 1, j + k) + 1;
            for (int i = right; i < left; ++i) {
                retVal.emplace_back(i);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int key;
        int k;
    };
    vector<subject> testData{{{3, 4, 9, 1, 3, 9, 5}, 9, 1}, {{2, 2, 2, 2, 2}, 2, 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [3,4,9,1,3,9,5], key = 9, k = 1
     *  Output: [1,2,3,4,5,6]
     *
     *  Input: nums = [2,2,2,2,2], key = 2, k = 2
     *  Output: [0,1,2,3,4]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], key = " << testData[i].key << ", k = " << testData[i].k << "\n";

        answer = cSolution.findKDistantIndices(testData[i].nums, testData[i].key, testData[i].k);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
