#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int waysToMakeFair(vector<int>& nums) {
        int retVal = 0;

        /* https://leetcode.com/problems/ways-to-make-a-fair-array/solutions/944544/java-python-python-easy-and-concise/
         *
         *  left[odd] + right[even] = left[even] + right[odd]
         *  +-----------------------------+---------------------------+
         *  | 0 | 1 | 2 | 3 | 4 | 5 | ... | 0 _ 2 _ 4 _ | _ 1 _ 3 _ 5 |
         *  +-----------------------------+---------------------------+
         *  |   | 1 | 2 | 3 | 4 | 5 | ... | x _ 2 _ 4 _ | _ 1 _ 3 _ 5 |
         *  | 0 |   | 2 | 3 | 4 | 5 | ... | x _ 2 _ 4 _ | 0 x _ 3 _ 5 |
         *  | 0 | 1 |   | 3 | 4 | 5 | ... | x 1 x _ 4 _ | 0 x _ 3 _ 5 |
         *  | 0 | 1 | 2 |   | 4 | 5 | ... | x 1 x _ 4 _ | 0 x 2 x _ 5 |
         *  | 0 | 1 | 2 | 3 |   | 5 | ... | x 1 x 3 x _ | 0 x 2 x _ 5 |
         *  | 0 | 1 | 2 | 3 | 4 |   | ... | x 1 x 3 x _ | 0 x 2 x 4 x |
         *  +-----------------------------+---------------------------+
         */

        int len = nums.size();

        vector<int> right(2, 0);
        for (int i = 0; i < len; ++i) {
            right[i % 2] += nums[i];
        }

        vector<int> left(2, 0);
        for (int i = 0; i < len; ++i) {
            right[i % 2] -= nums[i];
            if ((left[(i + 1) % 2] + right[i % 2]) == (left[i % 2] + right[(i + 1) % 2])) {
                ++retVal;
            }
            left[i % 2] += nums[i];
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{2, 1, 6, 4}}, {{1, 1, 1}}, {{1, 2, 3}}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    int answer = false;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.waysToMakeFair(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
