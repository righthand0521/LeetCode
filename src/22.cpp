#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    void backtracking(vector<string>& retVal, string str, int open, int close) {
        if ((open == 0) && (close == 0)) {
            retVal.emplace_back(str);
            return;
        }

        if (open > 0) {
            backtracking(retVal, str + "(", open - 1, close);
        }
        if (close > open) {
            backtracking(retVal, str + ")", open, close - 1);
        }
    }
    vector<string> generateParenthesis(int n) {
        vector<string> retVal;

        backtracking(retVal, "", n, n);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{3}, {1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 3
     *  Output: ["((()))","(()())","(())()","()(())","()()()"]
     *
     *  Input: n = 1
     *  Output: ["()"]
     */

    Solution cSolution;
    vector<string> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.generateParenthesis(testData[i].n);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << answer[j] << "\"";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
