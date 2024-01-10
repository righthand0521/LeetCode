#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int minOperations(vector<int>& nums) {
        int retVal = 0;

        unordered_map<int, int> hashTable;
        for (int num : nums) {
            auto iterator = hashTable.find(num);
            if (iterator != hashTable.end()) {
                hashTable[num]++;
            } else {
                hashTable[num] = 1;
            }
        }

        for (auto iterator : hashTable) {
            int times = iterator.second;
            if (times == 1) {
                retVal = -1;
                break;
            }

            retVal += (times / 3);
            if (times % 3 != 0) {
                retVal += 1;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{2, 3, 3, 2, 2, 4, 2, 3, 4}}, {{2, 1, 2, 2, 3, 3}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [2,3,3,2,2,4,2,3,4]
     *  Output: 4
     *
     *  Input: nums = [2,1,2,2,3,3]
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

        answer = cSolution.minOperations(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
