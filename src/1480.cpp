#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> runningSum(vector<int>& nums) {
        vector<int> retval;

        retval.push_back(nums[0]);
        for (long unsigned int i = 1; i < nums.size(); ++i) {
            retval.push_back(retval[i - 1] + nums[i]);
        }

        return retval;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 2, 3, 4}}, {{1, 1, 1, 1, 1}}, {{3, 1, 2, 10, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2,3,4]
     *  Output: [1,3,6,10]
     *
     *  Input: nums = [1,1,1,1,1]
     *  Output: [1,2,3,4,5]
     *
     *  Input: nums = [3,1,2,10,1]
     *  Output: [3,4,6,16,17]
     */
    
    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.runningSum(testData[i].nums);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
