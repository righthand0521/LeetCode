#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<string> buildArray(vector<int>& target, int n) {
        vector<string> retVal;

#define STR_PUSH "Push"
#define STR_POP "Pop"
        int targetSize = target.size();
        int targetIndex = 0;
        for (int i = 1; i <= n; ++i) {
            if (targetIndex >= targetSize) {
                break;
            }

            if (i == target[targetIndex]) {
                retVal.emplace_back(STR_PUSH);
                targetIndex += 1;
            } else {
                retVal.emplace_back(STR_PUSH);
                retVal.emplace_back(STR_POP);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> target;
        int n;
    };
    vector<subject> testData{{{1, 3}, 3}, {{1, 2, 3}, 3}, {{1, 2}, 4}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: target = [1,3], n = 3
     *  Output: ["Push","Push","Pop","Push"]
     *
     *  Input: target = [1,2,3], n = 3
     *  Output: ["Push","Push","Push"]
     *
     *  Input: target = [1,2], n = 4
     *  Output: ["Push","Push"]
     */

    Solution cSolution;
    vector<string> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: target = [";
        for (long unsigned int j = 0; j < testData[i].target.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].target[j];
        }
        cout << "], n = " << testData[i].n << "\n";

        answer = cSolution.buildArray(testData[i].target, testData[i].n);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << answer[j] << "\"";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
