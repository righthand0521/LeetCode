#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        int retVal = w;

        int profitsSize = profits.size();

        vector<pair<int, int>> projects;
        for (int i = 0; i < profitsSize; ++i) {
            projects.emplace_back(capital[i], profits[i]);
        }
        sort(projects.begin(), projects.end());

        priority_queue<int> priorityQueue;
        int ptr = 0;
        for (int i = 0; i < k; ++i) {
            while ((ptr < profitsSize) && (projects[ptr].first <= retVal)) {
                priorityQueue.push(projects[ptr++].second);
            }

            if (priorityQueue.empty()) {
                break;
            }

            retVal += priorityQueue.top();
            priorityQueue.pop();
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int k;
        int w;
        vector<int> profits;
        vector<int> capital;
    };
    vector<subject> testData{{2, 0, {1, 2, 3}, {0, 1, 1}}, {3, 0, {1, 2, 3}, {0, 1, 2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: k = 2, w = 0, profits = [1,2,3], capital = [0,1,1]
     *  Output: 4
     *
     *  Input: k = 3, w = 0, profits = [1,2,3], capital = [0,1,2]
     *  Output: 6
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: k = " << testData[i].k << ", w = " << testData[i].w << ", profits = [";
        for (long unsigned int j = 0; j < testData[i].profits.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].profits[j];
        }
        cout << "], capital = [";
        for (long unsigned int j = 0; j < testData[i].capital.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].capital[j];
        }
        cout << "]\n";

        answer = cSolution.findMaximizedCapital(testData[i].k, testData[i].w, testData[i].profits, testData[i].capital);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
