#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maximumElementAfterDecrementingAndRearranging(vector<int>& arr) {
        int retVal = 1;

        sort(arr.begin(), arr.end());

        int arrSize = arr.size();
        for (int i = 1; i < arrSize; ++i) {
            if (arr[i] - retVal >= 1) {
                retVal += 1;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> arr;
    };
    vector<subject> testData{
        {{2, 2, 1, 2, 1}}, {{100, 1, 1000}}, {{1, 2, 3, 4, 5}}, {{100, 1, 3, 3, 3, 3, 3}}, {{73, 98, 9}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: arr = [2,2,1,2,1]
     *  Output: 2
     *
     *  Input: arr = [100,1,1000]
     *  Output: 3
     *
     *  Input: arr = [1,2,3,4,5]
     *  Output: 5
     *
     *  Input: arr = [100,1,3,3,3,3,3]
     *  Output: 4
     *
     *  Input: arr = [73,98,9]
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

        answer = cSolution.maximumElementAfterDecrementingAndRearranging(testData[i].arr);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
