#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int findSmallestInteger(vector<int>& nums, int value) {
        int retVal = 0;

        vector<int> mp(value);
        for (auto& x : nums) {
            int v = (x % value + value) % value;
            mp[v]++;
        }

        while (mp[retVal % value] > 0) {
            mp[retVal % value]--;
            retVal++;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int value;
    };
    vector<subject> testData{{{1, -10, 7, 13, 6, 8}, 5}, {{1, -10, 7, 13, 6, 8}, 7}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,-10,7,13,6,8], value = 5
     *  Output: 4
     *
     *  Input: nums = [1,-10,7,13,6,8], value = 7
     *  Output: 2
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "], value = " << testData[i].value << "\n";

        answer = cSolution.findSmallestInteger(testData[i].nums, testData[i].value);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
