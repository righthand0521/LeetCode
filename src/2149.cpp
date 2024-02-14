#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> rearrangeArray(vector<int>& nums) {
        vector<int> retVal = nums;

        int positive = 0;
        int negative = 1;
        for (int num : nums) {
            if (num > 0) {
                retVal[positive] = num;
                positive += 2;
            } else {
                retVal[negative] = num;
                negative += 2;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{3, 1, -2, -5, 2, -4}}, {{-1, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [3,1,-2,-5,2,-4]
     *  Output: [3,-2,1,-5,2,-4]
     *
     *  Input: nums = [-1,1]
     *  Output: [1,-1]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.rearrangeArray(testData[i].nums);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
