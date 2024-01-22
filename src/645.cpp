#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> findErrorNums(vector<int>& nums) {
        vector<int> retVal(2, 0);

        int numsSize = nums.size() + 1;
        vector<int> hashTable(numsSize, 0);
        for (int num : nums) {
            hashTable[num]++;
        }

        for (int i = 1; i < numsSize; ++i) {
            if (hashTable[i] == 2) {
                retVal[0] = i;
            } else if (hashTable[i] == 0) {
                retVal[1] = i;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 2, 2, 4}}, {{1, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2,2,4]
     *  Output: [2,3]
     *
     *  Input: nums = [1,1]
     *  Output: [1,2]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.findErrorNums(testData[i].nums);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
