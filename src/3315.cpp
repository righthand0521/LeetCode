#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> minBitwiseArray(vector<int>& nums) {
        vector<int> retVal;

        for (int& num : nums) {
            int res = -1;
            int d = 1;
            while ((num & d) != 0) {
                res = num - d;
                d <<= 1;
            }
            retVal.emplace_back(res);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{2, 3, 5, 7}}, {{11, 13, 31}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [2,3,5,7]
     *  Output: [-1,1,4,3]
     *
     *  Input: nums = [11,13,31]
     *  Output: [9,12,15]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.minBitwiseArray(testData[i].nums);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
