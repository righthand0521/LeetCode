#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int lenLongestFibSubseq(vector<int>& arr) {
        int retVal = 0;

        int arrSize = arr.size();

        // dp[prev][curr] stores length of Fibonacci sequence ending at indexes prev,curr
        vector<vector<int>> dp(arrSize, vector<int>(arrSize, 0));

        // Find all possible pairs that sum to arr[curr]
        for (int curr = 2; curr < arrSize; curr++) {
            // Use two pointers to find pairs that sum to arr[curr]
            int start = 0;
            int end = curr - 1;
            while (start < end) {
                int pairSum = arr[start] + arr[end];
                if (pairSum > arr[curr]) {
                    end--;
                } else if (pairSum < arr[curr]) {
                    start++;
                } else {
                    // Found a valid pair, update dp
                    dp[end][curr] = dp[start][end] + 1;
                    retVal = max(retVal, dp[end][curr]);
                    end--;
                    start++;
                }
            }
        }

        // Add 2 to include first two numbers, or return 0 if no sequence found
        if (retVal != 0) {
            retVal += 2;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> arr;
    };
    vector<subject> testData{{{1, 2, 3, 4, 5, 6, 7, 8}}, {{1, 3, 7, 11, 12, 14, 18}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: arr = [1,2,3,4,5,6,7,8]
     *  Output: 5
     *
     *  Input: arr = [1,3,7,11,12,14,18]
     *  Output: 3
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: arr = [";
        for (long unsigned int j = 0; j < testData[i].arr.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].arr[j];
        }
        cout << "]\n";

        answer = cSolution.lenLongestFibSubseq(testData[i].arr);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
