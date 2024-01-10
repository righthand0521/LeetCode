#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> sortArrayByParity(vector<int>& nums) {
        vector<int> retVal;

        for (int num : nums) {
            if (num % 2 == 0) {
                retVal.emplace_back(num);
            }
        }
        for (int num : nums) {
            if (num % 2 == 1) {
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
    vector<subject> testData{{{3, 1, 2, 4}},    {{0}},          {{1, 5, 3, 7}},
                             {{1, 5, 9, 3, 7}}, {{2, 8, 4, 6}}, {{2, 8, 0, 4, 6}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [3,1,2,4]
     *  Output: [2,4,3,1]
     *
     *  Input: nums = [0]
     *  Output: [0]
     *
     *  Input: nums = [1,5,3,7]
     *  Output: [1,5,3,7]
     *
     *  Input: nums = [1,5,9,3,7]
     *  Output: [1,5,9,3,7]
     *
     *  Input: nums = [2,8,4,6]
     *  Output: [2,8,4,6]
     *
     *  Input: nums = [2,8,0,4,6]
     *  Output: [2,8,0,4,6]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.sortArrayByParity(testData[i].nums);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
