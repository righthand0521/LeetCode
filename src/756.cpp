#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// https://leetcode.cn/problems/pyramid-transition-matrix/solutions/3866474/tu-jie-hui-su-vis-you-hua-pythonjavacgo-9kcb9/
class Solution {
   private:
    bool dfs(vector<vector<vector<int>>>& groups, vector<int>& pyramid, vector<unsigned int>& vis, int i, int j) {
        bool retVal = false;

        if (i < 0) {
            retVal = true;
        } else if (vis[pyramid[i]]) {
            retVal = false;
        } else if (j == i + 1) {
            vis[pyramid[i]] = true;
            retVal = dfs(groups, pyramid, vis, i - 1, 0);
        } else {
            for (int top : groups[pyramid[i + 1] >> (j * 3) & 7][pyramid[i + 1] >> ((j + 1) * 3) & 7]) {
                pyramid[i] &= ~(7 << (j * 3));
                pyramid[i] |= top << (j * 3);
                if (dfs(groups, pyramid, vis, i, j + 1)) {
                    retVal = true;
                    break;
                }
            }
        }

        return retVal;
    }

   public:
    bool pyramidTransition(string bottom, vector<string>& allowed) {
        bool retVal = false;

        vector<vector<vector<int>>> groups(7, vector<vector<int>>(7));
        for (auto& s : allowed) {
            groups[s[0] & 31][s[1] & 31].push_back(s[2] & 31);
        }

        int bottomSize = bottom.size();
        vector<int> pyramid(bottomSize);
        for (int i = 0; i < bottomSize; i++) {
            pyramid[bottomSize - 1] |= (bottom[i] & 31) << (i * 3);
        }

        vector<unsigned int> vis(1 << ((bottomSize - 1) * 3));

        retVal = dfs(groups, pyramid, vis, bottomSize - 2, 0);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string bottom;
        vector<string> allowed;
    };
    vector<subject> testData{{"BCD", {"BCC", "CDE", "CEA", "FFF"}}, {"AAAA", {"AAB", "AAC", "BCD", "BBE", "DEF"}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: bottom = "BCD", allowed = ["BCC","CDE","CEA","FFF"]
     *  Output: true
     *
     *  Input: bottom = "AAAA", allowed = ["AAB","AAC","BCD","BBE","DEF"]
     *  Output: false
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: bottom = " << "\"" << testData[i].bottom << "\"";
        cout << ", allowed = [";
        for (long unsigned int j = 0; j < testData[i].allowed.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].allowed[j] << "\"";
        }
        cout << "]\n";

        answer = cSolution.pyramidTransition(testData[i].bottom, testData[i].allowed);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
