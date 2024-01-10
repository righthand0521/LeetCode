#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int findSpecialInteger(vector<int>& arr) {
        int retVal = 0;

        int arrSize = arr.size();
        int shift = arrSize >> 2;  // there is exactly one integer in the array that occurs more than 25% of the time
        for (int i = 0; i < (arrSize - shift); ++i) {
            if (arr[i] != arr[i + shift]) {
                continue;
            }
            retVal = arr[i];
            break;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> arr;
    };
    vector<subject> testData{{{1, 2, 2, 6, 6, 6, 6, 7, 10}}, {{1, 1}}, {{1, 1, 2, 2, 3, 3, 3, 3}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: arr = [1,2,2,6,6,6,6,7,10]
     *  Output: 6
     *
     *  Input: arr = [1,1]
     *  Output: 1
     *
     *  Input: [1,1,2,2,3,3,3,3]
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

        answer = cSolution.findSpecialInteger(testData[i].arr);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
