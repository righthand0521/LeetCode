#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
#define MODULO (int)(1e9 + 7)
    int numFactoredBinaryTrees(vector<int>& arr) {
        int retVal = 0;

        int arrSize = arr.size();

        sort(arr.begin(), arr.end());

        unordered_map<int, long> dp;
        for (int i = 0; i < arrSize; ++i) {
            dp[arr[i]] = 1;

            for (int j = 0; j < i; ++j) {
                if (arr[i] % arr[j] != 0) {
                    continue;
                }
                dp[arr[i]] = (dp[arr[i]] + dp[arr[j]] * dp[arr[i] / arr[j]]) % MODULO;
            }

            retVal = (retVal + dp[arr[i]]) % MODULO;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> arr;
    };
    vector<subject> testData{{{2, 4}}, {{2, 4, 5, 10}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: arr = [2,4]
     *  Output: 3
     *
     *  Input: arr = [2,4,5,10]
     *  Output: 7
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: arr = [";
        for (long unsigned int j = 0; j < testData[i].arr.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].arr[j];
        }
        cout << "]\n";

        answer = cSolution.numFactoredBinaryTrees(testData[i].arr);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
