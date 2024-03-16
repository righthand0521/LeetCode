#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int findMaxLength(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();

        int sum = 0;
        unordered_map<int, int> hashTable;
        hashTable[sum] = -1;
        for (int i = 0; i < numsSize; ++i) {
            if (nums[i] == 1) {
                sum++;
            } else if (nums[i] == 0) {
                sum--;
            }

            if (hashTable.count(sum) > 0) {
                retVal = max(retVal, i - hashTable[sum]);
            } else {
                hashTable[sum] = i;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{0, 1}}, {{0, 1, 0}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [0,1]
     *  Output: 2
     *
     *  Input: nums = [0,1,0]
     *  Output: 2
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.findMaxLength(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
