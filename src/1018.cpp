#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<bool> prefixesDivBy5(vector<int>& nums) {
        vector<bool> retVal;

        int prefix = 0;
        for (int num : nums) {
            prefix = ((prefix << 1) + num) % 5;
            retVal.emplace_back(prefix == 0);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{0, 1, 1}}, {{1, 1, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [0,1,1]
     *  Output: [true,false,false]
     *
     *  Input: nums = [1,1,1]
     *  Output: [false,false,false]
     */

    Solution cSolution;
    vector<bool> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.prefixesDivBy5(testData[i].nums);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << (answer[j] == true ? "true" : "false");
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
