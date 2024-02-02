#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> sequentialDigits(int low, int high) {
        vector<int> retVal;

        // 10 <= low <= high <= 10^9
        for (int i = 1; i < 10; ++i) {
            int num = i;
            for (int j = i + 1; j < 10; ++j) {
                num = 10 * num + j;
                if ((num >= low) && (num <= high)) {
                    retVal.emplace_back(num);
                }
            }
        }
        sort(retVal.begin(), retVal.end());

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int low;
        int high;
    };
    vector<subject> testData{{100, 300}, {1000, 13000}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: low = 100, high = 300
     *  Output: [123,234]
     *
     *  Input: low = 1000, high = 13000
     *  Output: [1234,2345,3456,4567,5678,6789,12345]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: low = " << testData[i].low << ", high = " << testData[i].high << "\n";

        answer = cSolution.sequentialDigits(testData[i].low, testData[i].high);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
