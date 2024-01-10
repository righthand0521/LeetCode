#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
#define MAX_IDEAS_CHAR (26)  // ideas[i] consists of lowercase English letters.
   public:
    // https://leetcode.cn/problems/naming-a-company/solutions/1596934/c-by-kotori-5-ztts/
    long long distinctNames(vector<string>& ideas) {
        long long retVal = 0;

        vector<vector<long long>> statistic(MAX_IDEAS_CHAR, vector<long long>(MAX_IDEAS_CHAR));
        unordered_set<string> ideaSet(ideas.begin(), ideas.end());

        for (string& idea : ideas) {
            int prefix = idea[0] - 'a';

            for (int i = 0; i < MAX_IDEAS_CHAR; ++i) {
                idea[0] = (i + 'a');
                if (ideaSet.count(idea) == 0) {
                    statistic[prefix][i]++;
                }
            }
        }

        for (int i = 0; i < MAX_IDEAS_CHAR; ++i) {
            for (int j = 0; j < MAX_IDEAS_CHAR; ++j) {
                retVal += (statistic[i][j] * statistic[j][i]);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> ideas;
    };
    vector<subject> testData{{{"coffee", "donuts", "time", "toffee"}}, {{"lack", "back"}}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: ideas = [";
        for (long unsigned int j = 0; j < testData[i].ideas.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].ideas[j];
        }
        cout << "]\n";

        answer = cSolution.distinctNames(testData[i].ideas);
        cout << "Output:" << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
