#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    bool isPossibleDivide(vector<int>& nums, int k) {
        bool retVal = false;

        int numsSize = nums.size();
        if (numsSize % k != 0) {
            return retVal;
        }

        sort(nums.begin(), nums.end());

        unordered_map<int, int> count;
        for (auto& num : nums) {
            count[num]++;
        }

        for (auto& x : nums) {
            if (count.count(x) == 0) {
                continue;
            }

            for (int i = 0; i < k; i++) {
                int num = x + i;
                if (count.count(num) == 0) {
                    return retVal;
                }

                count[num]--;
                if (count[num] == 0) {
                    count.erase(num);
                }
            }
        }
        retVal = true;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{
        {{1, 2, 3, 3, 4, 4, 5, 6}, 4}, {{3, 2, 1, 2, 3, 4, 3, 4, 5, 9, 10, 11}, 3}, {{1, 2, 3, 4}, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2,3,3,4,4,5,6], k = 4
     *  Output: true
     *
     *  Input: nums = [3,2,1,2,3,4,3,4,5,9,10,11], k = 3
     *  Output: true
     *
     *  Input: nums = [1,2,3,4], k = 3
     *  Output: false
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.isPossibleDivide(testData[i].nums, testData[i].k);
        cout << "Output: " << ((answer == true) ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
