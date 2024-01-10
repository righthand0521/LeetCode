#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    long long countSubarrays(vector<int>& nums, int minK, int maxK) {
        long long retVal = 0;

        /* Ref
         *  https://leetcode.com/problems/count-subarrays-with-fixed-bounds/solutions/2708099/java-c-python-sliding-window-with-explanation/
         *  https://leetcode.cn/problems/count-subarrays-with-fixed-bounds/solutions/1895734/fen-xi-ding-jie-zi-shu-zu-de-xing-zhi-yi-qusi/
         *  https://leetcode.cn/problems/count-subarrays-with-fixed-bounds/solutions/1895713/jian-ji-xie-fa-pythonjavacgo-by-endlessc-gag2/
         */
        int len = nums.size();
        long long badIdx = -1;
        long long minIdx = -1;
        long long maxIdx = -1;
        for (int i = 0; i < len; ++i) {
            if ((nums[i] < minK) || (nums[i] > maxK)) {
                badIdx = i;
            }

            if (nums[i] == minK) {
                minIdx = i;
            }

            if (nums[i] == maxK) {
                maxIdx = i;
            }

            /* avoid different type between a and b in max function
             *  Because std::max is a function template whose signature is, for example,
             *  template< class T >
             *  const T& max( const T& a, const T& b );
             */
            long long n1 = 0;
            long long n2 = min(minIdx, maxIdx) - badIdx;
            retVal += max(n1, n2);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int minK;
        int maxK;
    };
    vector<subject> testData{{{1, 3, 5, 2, 7, 5}, 1, 5}, {{1, 1, 1, 1}, 1, 1}};
    int numberOfTestCase = testData.size();
    /* Example 1:
     *  Input: nums = [1,3,5,2,7,5], minK = 1, maxK = 5
     *  Output: 2
     *
     *  Input: nums = [1,1,1,1], minK = 1, maxK = 1
     *  Output: 10
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], minK = " << testData[i].minK << ", maxK = " << testData[i].maxK << "\n";

        answer = cSolution.countSubarrays(testData[i].nums, testData[i].minK, testData[i].maxK);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
