#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int numIdenticalPairs(vector<int>& nums) {
        int retVal = 0;

        unordered_map<int, int> hashTable;
        for (auto num : nums) {
            auto iterator = hashTable.find(num);
            if (iterator != hashTable.end()) {
                retVal += hashTable[num];
            }
            hashTable[num] += 1;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 2, 3, 1, 1, 3}}, {{1, 1, 1, 1}}, {{1, 2, 3}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2,3,1,1,3]
     *  Output: 4
     *
     *  Input: nums = [1,1,1,1]
     *  Output: 6
     *
     *  Input: nums = [1,2,3]
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.numIdenticalPairs(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
