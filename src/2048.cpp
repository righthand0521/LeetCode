#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// https://leetcode.com/problems/next-greater-numerically-balanced-number/solutions/1537631/next-permutation-vs-dfs/
class Solution {
   private:
    int cnt[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    long long dfs(long long n, long long val, int sz) {
        long long retVal = 0;

        if (sz == 0) {
            for (int i = 1; i <= 9; ++i) {
                if ((cnt[i] != i) && (cnt[i] != 0)) {
                    return retVal;
                }
            }
            retVal = (val > n) ? (val) : (0);

            return retVal;
        }

        for (int i = 1; retVal == 0 && i <= 9; ++i)
            if ((cnt[i] > 0) && (cnt[i] <= sz)) {
                --cnt[i];
                retVal = dfs(n, val * 10 + i, sz - 1);
                ++cnt[i];
            }

        return retVal;
    }

   public:
    int nextBeautifulNumber(int n) {
        int retVal = 0;

        int sz = to_string(n).size();
        retVal = dfs(n, 0, sz);
        if (retVal == 0) {
            retVal = dfs(0, 0, sz + 1);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{1}, {1000}, {3000}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 1
     *  Output: 22
     *
     *  Input: n = 1000
     *  Output: 1333
     *
     *  Input: n = 3000
     *  Output: 3133
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.nextBeautifulNumber(testData[i].n);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
