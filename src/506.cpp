#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<string> findRelativeRanks(vector<int>& score) {
        vector<string> retVal;

        int scoreSize = score.size();
        vector<pair<int, int>> sortScore;
        for (int i = 0; i < scoreSize; ++i) {
            sortScore.emplace_back(i, score[i]);
        }
        sort(sortScore.begin(), sortScore.end(), [&](auto x1, auto x2) {
            // descending order
            return x1.second > x2.second;
        });

        retVal.resize(scoreSize);
        for (int i = 0; i < scoreSize; ++i) {
            if (i == 0) {
                retVal[sortScore[i].first] = "Gold Medal";
            } else if (i == 1) {
                retVal[sortScore[i].first] = "Silver Medal";
            } else if (i == 2) {
                retVal[sortScore[i].first] = "Bronze Medal";
            } else {
                retVal[sortScore[i].first] = to_string(i + 1);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> score;
    };
    vector<subject> testData{{{5, 4, 3, 2, 1}}, {{10, 3, 8, 9, 4}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: score = [5,4,3,2,1]
     *  Output: ["Gold Medal","Silver Medal","Bronze Medal","4","5"]
     *
     *  Input: score = [10,3,8,9,4]
     *  Output: ["Gold Medal","5","Bronze Medal","Silver Medal","4"]
     */

    Solution cSolution;
    vector<string> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: score = [";
        for (long unsigned int j = 0; j < testData[i].score.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].score[j];
        }
        cout << "]\n";

        answer = cSolution.findRelativeRanks(testData[i].score);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << answer[j] << "\"";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
