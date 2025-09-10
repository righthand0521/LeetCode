#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   public:
    int minimumTeachings(int n, vector<vector<int>>& languages, vector<vector<int>>& friendships) {
        int retVal = 0;

        unordered_set<int> cncon;
        for (auto friendship : friendships) {
            unordered_map<int, int> mp;
            for (int lan : languages[friendship[0] - 1]) {
                mp[lan] = 1;
            }

            bool conm = false;
            for (int lan : languages[friendship[1] - 1]) {
                if (mp[lan]) {
                    conm = true;
                    break;
                }
            }
            if (conm == false) {
                cncon.insert(friendship[0] - 1);
                cncon.insert(friendship[1] - 1);
            }
        }

        int maxCnt = 0;
        vector<int> cnt(n + 1, 0);
        for (auto friendship : cncon) {
            for (int lan : languages[friendship]) {
                cnt[lan]++;
                maxCnt = max(maxCnt, cnt[lan]);
            }
        }

        retVal = cncon.size() - maxCnt;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        vector<vector<int>> languages;
        vector<vector<int>> friendships;
    };
    vector<subject> testData{{2, {{1}, {2}, {1, 2}}, {{1, 2}, {1, 3}, {2, 3}}},
                             {3, {{2}, {1, 3}, {1, 2}, {3}}, {{1, 4}, {1, 2}, {3, 4}, {2, 3}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 2, languages = [[1],[2],[1,2]], friendships = [[1,2],[1,3],[2,3]]
     *  Output: 1
     *
     *  Input: n = 3, languages = [[2],[1,3],[1,2],[3]], friendships = [[1,4],[1,2],[3,4],[2,3]]
     *  Output: 2
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", languages = [";
        for (long unsigned int j = 0; j < testData[i].languages.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].languages[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].languages[j][k];
            }
            cout << "]";
        }
        cout << "], friendships = [";
        for (long unsigned int j = 0; j < testData[i].friendships.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].friendships[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].friendships[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.minimumTeachings(testData[i].n, testData[i].languages, testData[i].friendships);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
