#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool isGoodArray(vector<int>& nums) {
        bool retVal = false;

        /* Bézout's identity: https://en.wikipedia.org/wiki/B%C3%A9zout%27s_identity
         *  The basic idea is that for integers a and b,
         *  if gcd(a,b) = d, then there exist integers x and y, such that ax + by = d.
         *  This can be generalized for (n >= 2).
         *  if gcd(a,b,c) = d, then there exist integers x, y, and z, s.t, ax + by + cz = d.
         *
         *  Now this problem is just asking if gcd(x1, ......, xn) = 1
         */
        int len = nums.size();
        int d = __gcd(nums[0], nums[0]);
        for (int i = 1; i < len; ++i) {
            d = __gcd(d, nums[i]);
        }
        if (d == 1) {
            retVal = true;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{12, 5, 7, 23}}, {{29, 6, 10}}, {{3, 6}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [12,5,7,23]
     *  Output: true
     *
     *  Input: nums = [29,6,10]
     *  Output: true
     *
     *  Input: nums = [3,6]
     *  Output: false
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: hours = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.isGoodArray(testData[i].nums);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
