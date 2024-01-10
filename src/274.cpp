#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int hIndex(vector<int>& citations) {
        int retVal = 0;

        int citationsSize = citations.size();

        vector<int> countMap(citationsSize + 1, 0);
        int cited = 0;
        for (int citation : citations) {
            if (citation > citationsSize) {
                cited++;
            } else {
                countMap[citation]++;
            }
        }

        for (int i = citationsSize; i >= 0; --i) {
            cited += countMap[i];
            if (cited >= i) {
                retVal = i;
                break;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> citations;
    };
    vector<subject> testData{{{3, 0, 6, 1, 5}}, {{1, 3, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: citations = [3,0,6,1,5]
     *  Output: 3
     *
     *  Input: citations = [1,3,1]
     *  Output: 1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: citations = [";
        for (long unsigned int j = 0; j < testData[i].citations.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].citations[j];
        }
        cout << "]\n";

        answer = cSolution.hIndex(testData[i].citations);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
