#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
        vector<int> retVal;

        for (auto idx : nums) {
            int count = 0;
            for (auto num : nums) {
                if (idx > num) {
                    ++count;
                }
            }
            retVal.emplace_back(count);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{8, 1, 2, 2, 3}}, {{6, 5, 4, 8}}, {{7, 7, 7, 7}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [8,1,2,2,3]
     *  Output: [4,0,1,1,3]
     *
     *  Input: nums = [6,5,4,8]
     *  Output: [2,1,0,3]
     *
     *  Input: nums = [7,7,7,7]
     *  Output: [0,0,0,0]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.smallerNumbersThanCurrent(testData[i].nums);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
