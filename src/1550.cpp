#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool threeConsecutiveOdds(vector<int>& arr) {
        bool retVal = false;

        int consecutiveOdds = 0;
        for (int num : arr) {
            if (num % 2 == 0) {
                consecutiveOdds = 0;
            } else {
                consecutiveOdds += 1;
                if (consecutiveOdds == 3) {
                    retVal = true;
                    break;
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> arr;
    };
    vector<subject> testData{{{2, 6, 4, 1}}, {{1, 2, 34, 3, 4, 5, 7, 23, 12}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: arr = [2,6,4,1]
     *  Output: false
     *
     *  Input: arr = [1,2,34,3,4,5,7,23,12]
     *  Output: true
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: arr = [";
        for (long unsigned int j = 0; j < testData[i].arr.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].arr[j];
        }
        cout << "]\n";

        answer = cSolution.threeConsecutiveOdds(testData[i].arr);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
