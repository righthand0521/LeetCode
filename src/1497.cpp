#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    bool canArrange(vector<int>& arr, int k) {
        bool retVal = false;

        unordered_map<int, int> remainderCount;
        for (auto i : arr) {
            remainderCount[(i % k + k) % k]++;
        }

        for (auto i : arr) {
            int remainder = (i % k + k) % k;

            if (remainder == 0) {
                if (remainderCount[remainder] % 2 == 1) {
                    return retVal;
                }
            } else if (remainderCount[remainder] != remainderCount[k - remainder]) {
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
        int k;
    };
    vector<subject> testData{{{1, 2, 3, 4, 5, 10, 6, 7, 8, 9}, 5}, {{1, 2, 3, 4, 5, 6}, 7}, {{1, 2, 3, 4, 5, 6}, 10}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: arr = [1,2,3,4,5,10,6,7,8,9], k = 5
     *  Output: true
     *
     *  Input: arr = [1,2,3,4,5,6], k = 7
     *  Output: true
     *
     *  Input: arr = [1,2,3,4,5,6], k = 10
     *  Output: false
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: arr = [";
        for (long unsigned int j = 0; j < testData[i].arr.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].arr[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.canArrange(testData[i].arr, testData[i].k);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
