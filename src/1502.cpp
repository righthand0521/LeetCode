#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool canMakeArithmeticProgression(vector<int>& arr) {
        bool retVal = false;

        sort(arr.begin(), arr.end());
        for (long unsigned int i = 2; i < arr.size(); ++i) {
            if ((arr[i] - arr[i - 1]) != (arr[i - 1] - arr[i - 2])) {
                return retVal;
            }
        }
        retVal = true;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> arr;
    };
    vector<subject> testData{{{3, 5, 1}}, {{1, 2, 4}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: arr = [3,5,1]
     *  Output: true
     *
     *  Input: arr = [1,2,4]
     *  Output: false
     */

    Solution cSolution;
    bool answer = false;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: arr = [ ";
        for (long unsigned int j = 0; j < testData[i].arr.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].arr[j];
        }
        cout << "]\n";

        answer = cSolution.canMakeArithmeticProgression(testData[i].arr);
        cout << "Output: " << ((answer == true) ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
