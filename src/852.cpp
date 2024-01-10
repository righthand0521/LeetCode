#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int peakIndexInMountainArray(vector<int>& arr) {
        int retVal = 0;

        int arrSize = arr.size();
        int left = 0;
        int right = arrSize - 1;
        while (left < right) {
            int middle = left + (right - left) / 2;
            if (arr[middle] < arr[middle + 1]) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }
        retVal = left;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> arr;
    };
    vector<subject> testData{{{0, 1, 0}}, {{0, 2, 1, 0}}, {{0, 10, 5, 2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: arr = [0,1,0]
     *  Output: 1
     *
     *  Input: arr = [0,2,1,0]
     *  Output: 1
     *
     *  Input: arr = [0,10,5,2]
     *  Output: 1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: arr = [";
        for (long unsigned int j = 0; j < testData[i].arr.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].arr[j];
        }
        cout << "]\n";

        answer = cSolution.peakIndexInMountainArray(testData[i].arr);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
