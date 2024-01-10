#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    void backtracking(int k, int n, int start, vector<int>& combine, vector<vector<int>>& answer) {
        int combineSize = combine.size();
        if (combineSize > k) {
            return;
        } else if (n < 0) {
            return;
        } else if ((combineSize == k) && (n == 0)) {
            answer.push_back(combine);
            return;
        }

        // Only numbers 1 through 9 are used.
        for (int i = start; i < 10; ++i) {
            combine.push_back(i);
            backtracking(k, n - i, i + 1, combine, answer);
            combine.pop_back();
        }
    }
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> retVal;

        vector<int> combine;
        backtracking(k, n, 1, combine, retVal);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int k;
        int n;
    };
    vector<subject> testData{{3, 7}, {3, 9}, {4, 1}, {2, 18}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: k = 3, n = 7
     *  Output: [[1,2,4]]
     *
     *  Input: k = 3, n = 9
     *  Output: [[1,2,6],[1,3,5],[2,3,4]]
     *
     *  Input: k = 4, n = 1
     *  Output: []
     *
     *  Input: k = 2, n = 18
     *  Output: []
     */

    Solution cSolution;
    vector<vector<int>> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: k = " << testData[i].k << ", n = " << testData[i].n << "\n";

        answer = cSolution.combinationSum3(testData[i].k, testData[i].n);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < answer[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << answer[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
