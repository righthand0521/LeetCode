#include <algorithm>
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int longestSquareStreak(vector<int>& nums) {
        int retVal = 0;

        sort(nums.begin(), nums.end());

        unordered_map<int, int> hashTable;
        for (int num : nums) {
            int root = (int)sqrt(num);
            if ((root * root == num) && (hashTable.find(root) != hashTable.end())) {
                hashTable[num] = hashTable[root] + 1;
            } else {
                hashTable[num] = 1;
            }
        }

        for (auto iterator = hashTable.begin(); iterator != hashTable.end(); ++iterator) {
            retVal = max(retVal, iterator->second);
        }
        if (retVal == 1) {
            retVal = -1;  // return -1 if there is no square streak.
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{4, 3, 6, 16, 8, 2}}, {{2, 3, 5, 6, 7}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [4,3,6,16,8,2]
     *  Output: 3
     *
     *  Input: nums = [2,3,5,6,7]
     *  Output: -1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.longestSquareStreak(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
