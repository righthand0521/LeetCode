#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> sortByBits(vector<int>& arr) {
        vector<int> retVal;

        retVal = arr;
        sort(retVal.begin(), retVal.end(), [&](const int& a, const int& b) {
            if (__builtin_popcount(a) == __builtin_popcount(b)) {
                return a < b;
            }

            return __builtin_popcount(a) < __builtin_popcount(b);
        });

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> arr;
    };
    vector<subject> testData{{{0, 1, 2, 3, 4, 5, 6, 7, 8}}, {{1024, 512, 256, 128, 64, 32, 16, 8, 4, 2, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: arr = [0,1,2,3,4,5,6,7,8]
     *  Output: [0,1,2,4,8,3,5,6,7]
     *
     *  Input: arr = [1024,512,256,128,64,32,16,8,4,2,1]
     *  Output: [1,2,4,8,16,32,64,128,256,512,1024]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: arr = [";
        for (long unsigned int j = 0; j < testData[i].arr.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].arr[j];
        }
        cout << "]\n";

        answer = cSolution.sortByBits(testData[i].arr);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
