#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   public:
    int backtracking(int i, vector<int>& distribute, vector<int>& cookies, int k, int zeroCount) {
        int retVal = numeric_limits<int>::max();

        int cookiesSize = cookies.size();
        if (cookiesSize - i < zeroCount) {
            return retVal;
        }

        if (i == cookiesSize) {
            retVal = *max_element(distribute.begin(), distribute.end());
            return retVal;
        }

        for (int j = 0; j < k; ++j) {
            if (distribute[j] == 0) {
                zeroCount -= 1;
            }
            distribute[j] += cookies[i];

            retVal = min(retVal, backtracking(i + 1, distribute, cookies, k, zeroCount));

            distribute[j] -= cookies[i];
            if (distribute[j] == 0) {
                zeroCount += 1;
            }
        }

        return retVal;
    }
    int distributeCookies(vector<int>& cookies, int k) {
        int retVal = 0;

        vector<int> distribute(k, 0);
        retVal = backtracking(0, distribute, cookies, k, k);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> cookies;
        int k;
    };
    vector<subject> testData{{{8, 15, 10, 20, 8}, 2}, {{6, 1, 3, 2, 2, 4, 1, 2}, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: cookies = [8,15,10,20,8], k = 2
     *  Output: 31
     *
     *  Input: cookies = [6,1,3,2,2,4,1,2], k = 3
     *  Output: 7
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: cookies = [";
        for (long unsigned int j = 0; j < testData[i].cookies.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].cookies[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.distributeCookies(testData[i].cookies, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
