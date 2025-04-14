#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int countGoodTriplets(vector<int>& arr, int a, int b, int c) {
        int retVal = 0;

        int arrSize = arr.size();
        for (int i = 0; i < arrSize; ++i) {
            for (int j = i + 1; j < arrSize; ++j) {
                for (int k = j + 1; k < arrSize; ++k) {
                    if ((abs(arr[i] - arr[j]) <= a) && (abs(arr[j] - arr[k]) <= b) && (abs(arr[i] - arr[k]) <= c)) {
                        ++retVal;
                    }
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> arr;
        int a;
        int b;
        int c;
    };
    vector<subject> testData{{{3, 0, 1, 1, 9, 7}, 7, 2, 3}, {{1, 1, 2, 2, 3}, 0, 0, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: arr = [3,0,1,1,9,7], a = 7, b = 2, c = 3
     *  Output: 4
     *
     *  Input: arr = [1,1,2,2,3], a = 0, b = 0, c = 1
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: arr = [";
        for (long unsigned int j = 0; j < testData[i].arr.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].arr[j];
        }
        cout << "], a = " << testData[i].a << ", b = " << testData[i].b << ", c = " << testData[i].c << "\n";

        answer = cSolution.countGoodTriplets(testData[i].arr, testData[i].a, testData[i].b, testData[i].c);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
