#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> findArray(vector<int>& pref) {
        vector<int> retVal;

        retVal.emplace_back(pref[0]);  // 1 <= pref.length <= 10^5
        int prefSize = pref.size();
        for (int i = 1; i < prefSize; ++i) {
            retVal.emplace_back(pref[i - 1] ^ pref[i]);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> pref;
    };
    vector<subject> testData{{{5, 2, 0, 3, 1}}, {{13}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: pref = [5,2,0,3,1]
     *  Output: [5,7,2,3,2]
     *
     *  Input: pref = [13]
     *  Output: [13]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: pref = [";
        for (long unsigned int j = 0; j < testData[i].pref.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].pref[j];
        }
        cout << "]\n";

        answer = cSolution.findArray(testData[i].pref);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
