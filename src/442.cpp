#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> retVal;

        for (int num : nums) {
            int idx = abs(num);
            if (nums[idx - 1] > 0) {
                // in the range [1, n]
                nums[idx - 1] *= (-1);
            } else {
                // each integer appears once or twice
                retVal.emplace_back(idx);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{4, 3, 2, 7, 8, 2, 3, 1}}, {{1, 1, 2}}, {{1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [4,3,2,7,8,2,3,1]
     *  Output: [2,3]
     *
     *  Input: nums = [1,1,2]
     *  Output: [1]
     *
     *  Input: nums = [1]
     *  Output: []
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.findDuplicates(testData[i].nums);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
