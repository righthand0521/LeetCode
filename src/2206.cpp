#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    bool divideArray(vector<int>& nums) {
        bool retVal = true;

        int numsSize = nums.size();
        if ((numsSize % 2) == 1) {
            retVal = false;
            return retVal;
        }

        unordered_map<int, int> hashTable;
        for (int num : nums) {
            hashTable[num]++;
        }
        for (auto [key, value] : hashTable) {
            if ((value % 2) == 1) {
                retVal = false;
                break;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{3, 2, 3, 2, 2, 2}}, {{1, 2, 3, 4}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [3,2,3,2,2,2]
     *  Output: true
     *
     *  Input: nums = [1,2,3,4]
     *  Output: false
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.divideArray(testData[i].nums);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
