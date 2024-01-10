#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int arithmeticTriplets(vector<int>& nums, int diff) {
        int retVal = 0;

        unordered_map<int, int> hashTable;
        for (auto num : nums) {
            hashTable[num] = num;
        }
        for (auto num : nums) {
            if (hashTable.find(num + diff) == hashTable.end()) {
                continue;
            }
            if (hashTable.find(num + diff + diff) == hashTable.end()) {
                continue;
            }
            retVal += 1;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int diff;
    };
    vector<subject> testData{{{0, 1, 4, 6, 7, 10}, 3}, {{4, 5, 6, 7, 8, 9}, 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [0,1,4,6,7,10], diff = 3
     *  Output: 2
     *
     *  Input: nums = [4,5,6,7,8,9], diff = 2
     *  Output: 2
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], diff = " << testData[i].diff << "\n";

        answer = cSolution.arithmeticTriplets(testData[i].nums, testData[i].diff);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
