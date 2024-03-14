#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        int retVal = 0;

        unordered_map<int, int> hashTable;
        int sum = 0;
        for (int num : nums) {
            hashTable[sum] += 1;
            sum += num;
            retVal += hashTable[sum - goal];
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int goal;
    };
    vector<subject> testData{{{1, 0, 1, 0, 1}, 2}, {{0, 0, 0, 0, 0}, 0}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,0,1,0,1], goal = 2
     *  Output: 4
     *
     *  Input: nums = [0,0,0,0,0], goal = 0
     *  Output: 15
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "], goal = " << testData[i].goal << "\n";

        answer = cSolution.numSubarraysWithSum(testData[i].nums, testData[i].goal);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
