#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    void backtracking(vector<int>& candidates, int target, int idx, vector<int>& combine, vector<vector<int>>& answer) {
        if (target < 0) {
            return;
        } else if (target == 0) {
            answer.emplace_back(combine);
            return;
        }

        int candidatesSize = candidates.size();
        for (int i = idx; i < candidatesSize; i++) {
            if (candidates[i] > target) {
                break;
            }
            combine.push_back(candidates[i]);
            backtracking(candidates, target - candidates[i], i, combine, answer);
            combine.pop_back();
        }
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> retVal;

        if (candidates.empty() == true) {
            return retVal;
        }

        if (*min_element(candidates.begin(), candidates.end()) > target) {
            return retVal;
        }

        sort(candidates.begin(), candidates.end());
        vector<int> combine;
        backtracking(candidates, target, 0, combine, retVal);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> candidates;
        int target;
    };
    vector<subject> testData{{{2, 3, 6, 7}, 7}, {{2, 3, 5}, 8}, {{2}, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: candidates = [2,3,6,7], target = 7
     *  Output: [[2,2,3],[7]]
     *
     *  Input: candidates = [2,3,5], target = 8
     *  Output: [[2,2,2,2],[2,3,3],[3,5]]
     *
     *  Input: candidates = [2], target = 1
     *  Output: []
     */

    Solution cSolution;
    vector<vector<int>> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: candidates = [";
        for (long unsigned int j = 0; j < testData[i].candidates.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].candidates[j];
        }
        cout << "], target = " << testData[i].target << "\n";

        answer = cSolution.combinationSum(testData[i].candidates, testData[i].target);
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
