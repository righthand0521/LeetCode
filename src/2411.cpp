#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    int maxBit = 31;  // 0 <= nums[i] <= 10^9

   public:
    vector<int> smallestSubarrays(vector<int>& nums) {
        vector<int> retVal;

        int numsSize = nums.size();

        retVal.resize(numsSize, 0);
        vector<int> pos(maxBit, -1);
        for (int i = numsSize - 1; i >= 0; --i) {
            int j = i;
            for (int bit = 0; bit < maxBit; ++bit) {
                if (!(nums[i] & (1 << bit))) {
                    if (pos[bit] != -1) {
                        j = max(j, pos[bit]);
                    }
                } else {
                    pos[bit] = i;
                }
            }
            retVal[i] = j - i + 1;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 0, 2, 1, 3}}, {{1, 2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,0,2,1,3]
     *  Output: [3,3,2,2,1]
     *
     *  Input: nums = [1,2]
     *  Output: [2,1]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.smallestSubarrays(testData[i].nums);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
