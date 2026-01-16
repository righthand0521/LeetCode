#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   private:
    static constexpr int MODULO = 1e9 + 7;

    unordered_set<int> getEdges(vector<int>& fences, int border) {
        unordered_set<int> retVal;

        fences.emplace_back(1);
        fences.emplace_back(border);
        sort(fences.begin(), fences.end());
        int fenceSize = fences.size();
        for (int i = 0; i < fenceSize; i++) {
            for (int j = i + 1; j < fenceSize; j++) {
                retVal.insert(fences[j] - fences[i]);
            }
        }

        return retVal;
    }

   public:
    int maximizeSquareArea(int m, int n, vector<int>& hFences, vector<int>& vFences) {
        int retVal = 0;

        unordered_set<int> hEdges = getEdges(hFences, m);
        unordered_set<int> vEdges = getEdges(vFences, n);
        for (auto e : hEdges) {
            if (vEdges.find(e) != vEdges.end()) {
                retVal = max(retVal, e);
            }
        }

        if (retVal == 0) {
            retVal = -1;
        } else {
            retVal = 1ll * retVal * retVal % MODULO;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int m;
        int n;
        vector<int> fences;
        vector<int> vFences;
    };
    vector<subject> testData{{4, 3, {2, 3}, {2}}, {6, 7, {2}, {4}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: m = 4, n = 3, hFences = [2,3], vFences = [2]
     *  Output: 4
     *
     *  Input: m = 6, n = 7, hFences = [2], vFences = [4]
     *  Output: -1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: m = " << testData[i].m << ", n = " << testData[i].n << ", hFences = [";
        for (long unsigned int j = 0; j < testData[i].fences.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].fences[j];
        }
        cout << "], vFences = [";
        for (long unsigned int j = 0; j < testData[i].vFences.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].vFences[j];
        }
        cout << "]\n";

        answer = cSolution.maximizeSquareArea(testData[i].m, testData[i].n, testData[i].fences, testData[i].vFences);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
