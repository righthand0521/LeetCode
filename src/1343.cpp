#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int numOfSubarrays(vector<int>& arr, int k, int threshold) {
        int retVal = 0;

        int arrSize = arr.size();

        long long prefixSum = 0;  // 1 <= arr.length <= 10^5, 1 <= arr[i] <= 10^4, 1 <= k <= arr.length
        for (int i = 0; i < (k - 1); ++i) {
            prefixSum += arr[i];
        }

        for (int i = (k - 1); i < arrSize; ++i) {
            prefixSum += arr[i];
            if ((prefixSum / k) >= threshold) {
                ++retVal;
            }

            prefixSum -= arr[i - k + 1];
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> arr;
        int k;
        int threshold;
    };
    vector<subject> testData{{{2, 2, 2, 2, 5, 5, 5, 8}, 3, 4}, {{11, 13, 17, 23, 29, 31, 7, 5, 2, 3}, 3, 5}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: arr = [2,2,2,2,5,5,5,8], k = 3, threshold = 4
     *  Output: 3
     *
     *  Input: arr = [11,13,17,23,29,31,7,5,2,3], k = 3, threshold = 5
     *  Output: 6
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: arr = [";
        for (long unsigned int j = 0; j < testData[i].arr.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].arr[j];
        }
        cout << "], k = " << testData[i].k << ", threshold = " << testData[i].threshold << "\n";

        answer = cSolution.numOfSubarrays(testData[i].arr, testData[i].k, testData[i].threshold);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
