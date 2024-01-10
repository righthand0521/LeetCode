#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    void backtracking(int cur, int n, int k, vector<vector<int>>& answer, vector<int>& temp) {
        int tempSize = temp.size();

        if (tempSize + (n - cur + 1) < k) {
            return;
        }

        if (tempSize == k) {
            answer.push_back(temp);
            return;
        }

        temp.push_back(cur);
        backtracking(cur + 1, n, k, answer, temp);
        temp.pop_back();
        backtracking(cur + 1, n, k, answer, temp);
    }
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> retVal;

        vector<int> temp;
        backtracking(1, n, k, retVal, temp);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        int k;
    };
    vector<subject> testData{{4, 2}, {1, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 4, k = 2
     *  Output: [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
     *
     *  Input: n = 1, k = 1
     *  Output: [[1]]
     */

    Solution cSolution;
    vector<vector<int>> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", k = " << testData[i].k << "\n";

        answer = cSolution.combine(testData[i].n, testData[i].k);
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
