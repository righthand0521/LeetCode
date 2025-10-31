#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> getSneakyNumbers(vector<int>& nums) {
        vector<int> retVal;

        unordered_map<int, int> hashTable;
        for (int num : nums) {
            hashTable[num] += 1;
            if (hashTable[num] == 2) {
                retVal.emplace_back(num);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{0, 1, 1, 0}}, {{0, 3, 2, 1, 3, 2}}, {{7, 1, 5, 4, 3, 4, 6, 0, 9, 5, 8, 2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [0,1,1,0]
     *  Output: [0,1]
     *
     *  Input: nums = [0,3,2,1,3,2]
     *  Output: [2,3]
     *
     *  Input: nums = [7,1,5,4,3,4,6,0,9,5,8,2]
     *  Output: [4,5]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.getSneakyNumbers(testData[i].nums);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
