#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   public:
    int repeatedNTimes(vector<int>& nums) {
        int retVal = 0;

        unordered_set<int> numSet;
        for (const int& num : nums) {
            if (numSet.find(num) != numSet.end()) {
                retVal = num;
                break;
            }
            numSet.insert(num);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 2, 3, 3}}, {{2, 1, 2, 5, 3, 2}}, {{5, 1, 5, 2, 5, 3, 5, 4}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2,3,3]
     *  Output: 3
     *
     *  Input: nums = [2,1,2,5,3,2]
     *  Output: 2
     *
     *  Input: nums = [5,1,5,2,5,3,5,4]
     *  Output: 5
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.repeatedNTimes(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
