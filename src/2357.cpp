#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int minimumOperations(vector<int>& nums) {
        int retVal = 0;

        unordered_map<int, int> hashTable;
        for (auto num : nums) {
            if (num == 0) {  // Each element in nums is already 0 so no operations are needed.
                continue;
            }

            auto iterator = hashTable.find(num);
            if (iterator == hashTable.end()) {
                ++retVal;
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
    vector<subject> testData{{{1, 5, 0, 3, 5}}, {{0}}};
    int numberOfTestCase = testData.size();
    /* Example:
     *  Input: nums = [1,5,0,3,5]
     *  Output: 3
     *
     *  Input: nums = [0]
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.minimumOperations(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
