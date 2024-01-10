#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    bool containsDuplicate(vector<int>& nums) {
        bool retVal = false;

        unordered_map<int, int> hashTable;
        for (auto num : nums) {
            auto iterator = hashTable.find(num);
            if (iterator != hashTable.end()) {
                retVal = true;
                break;
            }
            hashTable[num] = 1;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 2, 3, 1}}, {{1, 2, 3, 4}}, {{1, 1, 1, 3, 3, 4, 3, 2, 4, 2}}};
    int numberOfTestCase = testData.size();
    /* Example:
     *  Input: nums = [1,2,3,1]
     *  Output: true
     *
     *  Input: nums = [1,2,3,4]
     *  Output: false
     *
     *  Input: nums = [1,1,1,3,3,4,3,2,4,2]
     *  Output: true
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.containsDuplicate(testData[i].nums);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
