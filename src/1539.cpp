#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
#define BINARY_SEARCH (1)
   public:
    int findKthPositive(vector<int>& arr, int k) {
        int retVal = 0;

        int arrSize = arr.size();

#if (BINARY_SEARCH)
        cout << "BINARY_SEARCH\n";

        int left = 0;
        int right = arrSize;
        while (left < right) {
            int middle = left + (right - left) / 2;
            if (arr[middle] - middle >= k + 1) {
                right = middle;
            } else {
                left = middle + 1;
            }
        }
        retVal = k + left;
#else
        for (int i = 0; i < arrSize; ++i) {
            ++retVal;
            if (retVal != arr[i]) {
                --i;
                --k;
            }

            if (k == 0) {
                break;
            }
        }

        while (k > 0) {
            ++retVal;
            --k;
        }
#endif

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> arr;
        int k;
    };
    vector<subject> testData{{{2, 3, 4, 7, 11}, 5}, {{1, 2, 3, 4}, 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: arr = [2,3,4,7,11], k = 5
     *  Output: 9
     *
     *  Input: arr = [1,2,3,4], k = 2
     *  Output: 6
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: arr = [";
        for (long unsigned int j = 0; j < testData[i].arr.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].arr[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.findKthPositive(testData[i].arr, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
