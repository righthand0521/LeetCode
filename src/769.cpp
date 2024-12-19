#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxChunksToSorted(vector<int>& arr) {
        int retVal = 0;

        int arrSize = arr.size();
        int maxElement = 0;
        for (int i = 0; i < arrSize; i++) {
            maxElement = max(maxElement, arr[i]);
            // All values in range [0, i] belong to the prefix arr[0:i]; a new chunk can be formed
            if (maxElement == i) {
                retVal++;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> arr;
    };
    vector<subject> testData{{{4, 3, 2, 1, 0}}, {{1, 0, 2, 3, 4}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: arr = [4,3,2,1,0]
     *  Output: 1
     *
     *  Input: arr = [1,0,2,3,4]
     *  Output: 4
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: arr = [";
        for (long unsigned int j = 0; j < testData[i].arr.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].arr[j];
        }
        cout << "]\n";

        answer = cSolution.maxChunksToSorted(testData[i].arr);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
