#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int findDuplicate(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();
        vector<int> count(numsSize, 0);
        for (auto num : nums) {
            if (count[num] != 0){
                retVal = num;
                break;
            }
            count[num]++;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 3, 4, 2, 2}}, {{3, 1, 3, 4, 2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,3,4,2,2]
     *  Output: 2
     *
     *  nums = [3,1,3,4,2]
     *  Output: 3
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.findDuplicate(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
