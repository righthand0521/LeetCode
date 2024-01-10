#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int getWinner(vector<int>& arr, int k) {
        int retVal = 0;

        int arrSize = arr.size();

        int winRounds = 0;
        int winIdx = 0;
        int nextIdx;
        for (nextIdx = 1; nextIdx < arrSize; ++nextIdx) {  // 2 <= arr.length <= 10^5
            if (arr[winIdx] > arr[nextIdx]) {
                winRounds += 1;
            } else if (arr[winIdx] < arr[nextIdx]) {
                winIdx = nextIdx;
                winRounds = 1;
            } else if (arr[winIdx] == arr[nextIdx]) {
                // arr contains distinct integers.
                continue;
            }

            if (winRounds == k) {
                break;
            }
        }
        retVal = arr[winIdx];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> arr;
        int k;
    };
    vector<subject> testData{{{2, 1, 3, 5, 4, 6, 7}, 2},
                             {{3, 2, 1}, 10},
                             {{1, 11, 22, 33, 44, 55, 66, 77, 88, 99}, 1000000000},
                             {{1, 25, 35, 42, 68, 70}, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: arr = [2,1,3,5,4,6,7], k = 2
     *  Output: 5
     *
     *  Input: arr = [3,2,1], k = 10
     *  Output: 3
     *
     *  Input: arr = [1,11,22,33,44,55,66,77,88,99], k = 1000000000
     *  Output: 99
     *
     *  Input: arr = [1,25,35,42,68,70], k = 1
     *  Output: 25
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: arr = [";
        for (long unsigned int j = 0; j < testData[i].arr.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].arr[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.getWinner(testData[i].arr, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
