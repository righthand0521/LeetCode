#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maximizeSquareHoleArea(int n, int m, vector<int>& hBars, vector<int>& vBars) {
        int retVal = 0;

        sort(hBars.begin(), hBars.end());
        int hBarsSize = hBars.size();
        int hmax = 1;
        int hcur = 1;
        for (int i = 1; i < hBarsSize; i++) {
            if (hBars[i] == hBars[i - 1] + 1) {
                hcur++;
            } else {
                hcur = 1;
            }
            hmax = max(hmax, hcur);
        }

        sort(vBars.begin(), vBars.end());
        int vBarsSize = vBars.size();
        int vmax = 1;
        int vcur = 1;
        for (int i = 1; i < vBarsSize; i++) {
            if (vBars[i] == vBars[i - 1] + 1) {
                vcur++;
            } else {
                vcur = 1;
            }
            vmax = max(vmax, vcur);
        }

        int side = min(hmax, vmax) + 1;
        retVal = side * side;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        int m;
        vector<int> hBars;
        vector<int> vBars;
    };
    vector<subject> testData{{2, 1, {2, 3}, {2}}, {1, 1, {2}, {2}}, {2, 3, {2, 3}, {2, 4}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 2, m = 1, hBars = [2,3], vBars = [2]
     *  Output: 4
     *
     *  Input: n = 1, m = 1, hBars = [2], vBars = [2]
     *  Output: 4
     *
     *  Input: n = 2, m = 3, hBars = [2,3], vBars = [2,4]
     *  Output: 4
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", m = " << testData[i].m << ", hBars = [";
        for (long unsigned int j = 0; j < testData[i].hBars.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].hBars[j];
        }
        cout << "], vBars = [";
        for (long unsigned int j = 0; j < testData[i].vBars.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].vBars[j];
        }
        cout << "]\n";

        answer = cSolution.maximizeSquareHoleArea(testData[i].n, testData[i].m, testData[i].hBars, testData[i].vBars);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
