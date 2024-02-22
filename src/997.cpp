#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int findJudge(int n, vector<vector<int>>& trust) {
        int retVal = -1;

        vector<int> Outdegree(n);
        vector<int> Indegree(n);
        for (auto& edge : trust) {
            // Outdegree: ai; the person labeled ai trusts the person labeled bi
            ++Outdegree[edge[0] - 1];

            // Indegree: bi; the person labeled ai trusts the person labeled bi
            ++Indegree[edge[1] - 1];
        }

        for (int i = 0; i < n; ++i) {
            // The town judge trusts nobody.
            if (Outdegree[i] != 0) {
                continue;
            }

            // Everybody (except for the town judge) trusts the town judge.
            if (Indegree[i] != n - 1) {
                continue;
            }

            // There is exactly one person that satisfies properties 1 and 2.
            retVal = i + 1;
            break;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        vector<vector<int>> trust;
    };
    vector<subject> testData{{2, {{1, 2}}}, {3, {{1, 3}, {2, 3}}}, {3, {{1, 3}, {2, 3}, {3, 1}}}, {1, {}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 2, trust = [[1,2]]
     *  Output: 2
     *
     *  Input: n = 3, trust = [[1,3],[2,3]]
     *  Output: 3
     *
     *  Input: n = 3, trust = [[1,3],[2,3],[3,1]]
     *  Output: -1
     *
     *  Input: n = 1, trust = []
     *  Output: 1
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", trust = [";
        for (long unsigned int j = 0; j < testData[i].trust.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].trust[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].trust[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.findJudge(testData[i].n, testData[i].trust);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
