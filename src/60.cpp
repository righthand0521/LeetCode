#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    int permutation(int n) {
        int retVal = 1;

        int i;
        for (i = 1; i <= n; ++i) {
            retVal *= i;
        }

        return retVal;
    }

   public:
    string getPermutation(int n, int k) {
        string retVal = "";

        vector<char> buf(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            buf[i] = (i + 1) + '0';
        }

        vector<char> ans(n + 1, 0);
        int sum = 0;
        int i, j;
        for (i = 1; i <= n - 1; ++i) {
            int interval = permutation(n - i);

            for (j = 1; j <= n; ++j) {
                sum += interval;
                if (sum >= k) {
                    sum -= interval;
                    break;
                }
            }
            if (sum >= k) {
                break;
            }

            ans[i - 1] = buf[j - 1];
            for (int idx = j - 1; idx < n; ++idx) {
                buf[idx] = buf[idx + 1];
            }
        }
        ans[i - 1] = buf[0];
        for (i = 0; i < n; ++i) {
            retVal.push_back(ans[i]);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        int k;
    };
    vector<subject> testData{{3, 3}, {4, 9}, {3, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 3, k = 3
     *  Output: "213"
     *
     *  Input: n = 4, k = 9
     *  Output: "2314"
     *
     *  Input: n = 3, k = 1
     *  Output: "123"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", k = " << testData[i].k << "\n";

        answer = cSolution.getPermutation(testData[i].n, testData[i].k);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
