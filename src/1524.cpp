#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
#define MODULO (int)(1e9 + 7)  // Since the answer can be very large, return it modulo 10^9 + 7.
   public:
    int numOfSubarrays(vector<int>& arr) {
        int retVal = 0;

        int prefixSum = 0;
        int oddCount = 0;
        int evenCount = 1;  // evenCount starts as 1 since the initial sum (0) is even
        for (int num : arr) {
            prefixSum += num;
            if (prefixSum % 2 == 0) {  // If current prefix sum is even, add the number of odd subarrays
                retVal += oddCount;
                evenCount++;
            } else {  // If current prefix sum is odd, add the number of even subarrays
                retVal += evenCount;
                oddCount++;
            }

            retVal %= MODULO;  // To handle large results
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> arr;
    };
    vector<subject> testData{{{1, 3, 5}}, {{2, 4, 6}}, {{1, 2, 3, 4, 5, 6, 7}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: arr = [1,3,5]
     *  Output: 4
     *
     *  Input: arr = [2,4,6]
     *  Output: 0
     *
     *  Input: arr = [1,2,3,4,5,6,7]
     *  Output: 16
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: arr = [";
        for (long unsigned int j = 0; j < testData[i].arr.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].arr[j];
        }
        cout << "]\n";

        answer = cSolution.numOfSubarrays(testData[i].arr);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
