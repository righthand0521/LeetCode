#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
   private:
    int MODULO = (int)(1e9 + 7);

   public:
    int sumSubarrayMins(vector<int>& arr) {
        int retVal = 0;

        int arrSize = arr.size();

        stack<int> monoStack;
        vector<int> dp(arrSize, 0);
        for (int i = 0; i < arrSize; ++i) {
            int value = arr[i];
            while ((monoStack.empty() == false) && (arr[monoStack.top()] > value)) {
                monoStack.pop();
            }

            int key = i + 1;
            if (monoStack.empty() == false) {
                key = i - monoStack.top();
            }

            dp[i] = key * value;
            if (monoStack.empty() == false) {
                dp[i] += dp[i - key];
            }

            monoStack.push(i);

            retVal = (retVal + dp[i]) % MODULO;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> arr;
    };
    vector<subject> testData{{{3, 1, 2, 4}}, {{11, 81, 94, 43, 3}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: arr = [3,1,2,4]
     *  Output: 17
     *
     *  Input: arr = [11,81,94,43,3]
     *  Output: 444
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: arr = [";
        for (long unsigned int j = 0; j < testData[i].arr.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].arr[j];
        }
        cout << "]\n";

        answer = cSolution.sumSubarrayMins(testData[i].arr);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
