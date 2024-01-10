#include <algorithm>
#include <cmath>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   public:
    void dfs(int n, int k, int node, unordered_set<int>& visit, string& answer) {
        int highest = pow(10, n - 1);

        for (int x = 0; x < k; ++x) {
            int neighbor = node * 10 + x;
            if (visit.count(neighbor) == 0) {
                visit.insert(neighbor);
                dfs(n, k, neighbor % highest, visit, answer);
                answer += (x + '0');
            }
        }
    }
    string crackSafe(int n, int k) {
        string retVal = "";

        unordered_set<int> visit;
        dfs(n, k, 0, visit, retVal);
        retVal += string(n - 1, '0');

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        int k;
    };
    vector<subject> testData{{1, 2}, {2, 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 1, k = 2
     *  Output: "10"
     *
     *  Input: n = 2, k = 2
     *  Output: "01100"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", k = " << testData[i].k << "\n";

        answer = cSolution.crackSafe(testData[i].n, testData[i].k);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
