#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
#define ARRAY_BRUTE_FORCE (0)      // Time Complexity: O(n^3), Space Complexity: O(1).
#define ARRAY_TWO_LOOP (0)         // Time Complexity: O(n^2), Space Complexity: O(1).
#define MATH_INDEX_OCCURRENCE (1)  // Time Complexity: O(n), Space Complexity: O(1).
    int sumOddLengthSubarrays(vector<int>& arr) {
        int retVal = 0;

        int arrSize = arr.size();
#if (ARRAY_BRUTE_FORCE)
        cout << "Approach 1: Brute Force"
             << "\n";

        int sum, idx;
        int start, end;
        for (start = 0; start < arrSize; ++start) {
            for (end = start; end < arrSize; ++end) {
                if (((end - start + 1) % 2) == 0) {
                    continue;
                }
                sum = 0;
                for (idx = start; idx <= end; ++idx) {
                    sum += arr[idx];
                }
                retVal += sum;
            }
        }
#elif (ARRAY_TWO_LOOP)
        cout << "Approach 2: Two Loops"
             << "\n";

        int sum;
        int start, end;
        for (start = 0; start < arrSize; ++start) {
            sum = 0;
            for (end = start; end < arrSize; ++end) {
                sum += arr[end];
                if (((end - start + 1) % 2) == 1) {
                    retVal += sum;
                }
            }
        }
#elif (MATH_INDEX_OCCURRENCE)
        cout << "Approach 3: Check the occurrence of each index"
             << "\n";

        int oddLeft, oddRight;
        int evenLeft, evenRight;
        int head, tail;
        int i;
        for (i = 0; i < arrSize; ++i) {
            head = i;
            tail = arrSize - i - 1;

            oddLeft = (head / 2) + 1;
            oddRight = (tail / 2) + 1;
            evenLeft = (head + 1) / 2;
            evenRight = (tail + 1) / 2;

            retVal += (arr[i] * (oddLeft * oddRight));
            retVal += (arr[i] * (evenLeft * evenRight));
        }
#endif

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> arr;
    };
    vector<subject> testData{{{1, 4, 2, 5, 3}}, {{1, 2}}, {{10, 11, 12}}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    int answer = false;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: arr = [ ";
        for (long unsigned int j = 0; j < testData[i].arr.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].arr[j];
        }
        cout << "]\n";

        answer = cSolution.sumOddLengthSubarrays(testData[i].arr);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
