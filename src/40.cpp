#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    void backtracking(vector<int>& candidates, int target, int idx, int* back, vector<int>& combine,
                      vector<vector<int>>& answer) {
        if (target == 0) {
            answer.emplace_back(combine);
            return;
        }

        int candidatesSize = candidates.size();
        if (idx == candidatesSize) {
            return;
        }

        for (int i = idx; i < candidatesSize; ++i) {
            if (candidates[i] > target) {
                break;
            }

            if (candidates[i] == (*back)) {
                continue;
            }
            combine.emplace_back(candidates[i]);
            backtracking(candidates, target - candidates[i], i + 1, back, combine, answer);
            (*back) = combine.back();
            combine.pop_back();
        }
    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> retVal;

        if (candidates.empty() == true) {
            return retVal;
        }

        if (*min_element(candidates.begin(), candidates.end()) > target) {
            return retVal;
        }

        int back = 0;  // 1 <= candidates[i] <= 50
        vector<int> combine;
        sort(candidates.begin(), candidates.end());
        backtracking(candidates, target, 0, &back, combine, retVal);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> candidates;
        int target;
    };
    vector<subject> testData{{{10, 1, 2, 7, 6, 1, 5}, 8}, {{2, 5, 2, 1, 2}, 5}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: candidates = [10,1,2,7,6,1,5], target = 8
     *  Output: [[1,1,6],[1,2,5],[1,7],[2,6]]
     *
     *  Input: candidates = [2,5,2,1,2], target = 5
     *  Output: [[1,2,2],[5]]
     */

    Solution cSolution;
    vector<vector<int>> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: candidates = [";
        for (long unsigned int j = 0; j < testData[i].candidates.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].candidates[j];
        }
        cout << "], target = " << testData[i].target << "\n";

        answer = cSolution.combinationSum2(testData[i].candidates, testData[i].target);
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
