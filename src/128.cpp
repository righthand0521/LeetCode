#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int longestConsecutive(vector<int>& nums) {
        int retVal = 0;

        unordered_map<int, int> hashTable;
        for (int num : nums) {
            if (hashTable.find(num) != hashTable.end()) {
                continue;
            }

            int left = 0;
            if (hashTable.find(num - 1) != hashTable.end()) {
                left = hashTable[num - 1];
            }

            int right = 0;
            if (hashTable.find(num + 1) != hashTable.end()) {
                right = hashTable[num + 1];
            }

            int length = left + right + 1;
            hashTable[num] = 1;
            hashTable[num - left] = length;
            hashTable[num + right] = length;

            retVal = max(retVal, length);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{100, 4, 200, 1, 3, 2}}, {{0, 3, 7, 2, 5, 8, 4, 6, 0, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [100,4,200,1,3,2]
     *  Output: 4
     *
     *  Input: nums = [0,3,7,2,5,8,4,6,0,1]
     *  Output: 9
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.longestConsecutive(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
