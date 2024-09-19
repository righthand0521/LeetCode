#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    void initializeBaseCases(string& expression, vector<vector<vector<int>>>& dp) {
        int expressionSize = expression.size();

        for (int i = 0; i < expressionSize; i++) {
            if (isdigit(expression[i]) == 0) {
                continue;
            }

            int dig1 = expression[i] - '0';
            if ((i + 1 < expressionSize) && (isdigit(expression[i + 1]))) {
                int dig2 = expression[i + 1] - '0';
                int number = dig1 * 10 + dig2;
                dp[i][i + 1].emplace_back(number);
            }

            dp[i][i].emplace_back(dig1);
        }
    }
    void processSubexpression(string& expression, vector<vector<vector<int>>>& dp, int start, int end) {
        for (int split = start; split <= end; split++) {
            if (isdigit(expression[split])) {
                continue;
            }

            vector<int> leftResults = dp[start][split - 1];
            vector<int> rightResults = dp[split + 1][end];
            computeResults(expression[split], leftResults, rightResults, dp[start][end]);
        }
    }
    void computeResults(char op, vector<int>& leftResults, vector<int>& rightResults, vector<int>& results) {
        for (int leftValue : leftResults) {
            for (int rightValue : rightResults) {
                switch (op) {
                    case '+':
                        results.emplace_back(leftValue + rightValue);
                        break;
                    case '-':
                        results.emplace_back(leftValue - rightValue);
                        break;
                    case '*':
                        results.emplace_back(leftValue * rightValue);
                        break;
                }
            }
        }
    }

   public:
    vector<int> diffWaysToCompute(string expression) {
        vector<int> retVal;

        int expressionSize = expression.size();

        vector<vector<vector<int>>> dp(expressionSize, vector<vector<int>>(expressionSize));

        initializeBaseCases(expression, dp);

        for (int length = 3; length <= expressionSize; length++) {
            for (int start = 0; start + length - 1 < expressionSize; start++) {
                int end = start + length - 1;
                processSubexpression(expression, dp, start, end);
            }
        }

        retVal = dp[0][expressionSize - 1];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string expression;
    };
    vector<subject> testData{{"2-1-1"}, {"2*3-4*5"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: expression = "2-1-1"
     *  Output: [0,2]
     *
     *  Input: expression = "2*3-4*5"
     *  Output: [-34,-14,-10,-10,10]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: expression = \"" << testData[i].expression << "\"\n";

        answer = cSolution.diffWaysToCompute(testData[i].expression);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
