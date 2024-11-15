#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int findLengthOfShortestSubarray(vector<int>& arr) {
        int retVal = 0;

        int arrSize = arr.size();

        int right = arrSize - 1;
        while ((right > 0) && (arr[right] >= arr[right - 1])) {
            right--;
        }
        retVal = right;

        int left = 0;
        while ((left < right) && ((left == 0) || (arr[left - 1] <= arr[left]))) {
            while ((right < arrSize) && (arr[left] > arr[right])) {
                right++;
            }
            retVal = min(retVal, right - left - 1);
            left++;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> arr;
    };
    vector<subject> testData{{{1, 2, 3, 10, 4, 2, 3, 5}}, {{5, 4, 3, 2, 1}}, {{1, 2, 3}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: arr = [1,2,3,10,4,2,3,5]
     *  Output: 3
     *
     *  Input: arr = [5,4,3,2,1]
     *  Output: 4
     *
     *  Input: arr = [1,2,3]
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: arr = [";
        for (long unsigned int j = 0; j < testData[i].arr.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].arr[j];
        }
        cout << "]\n";

        answer = cSolution.findLengthOfShortestSubarray(testData[i].arr);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
