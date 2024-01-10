#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people) {
        vector<int> retVal;

        int req_skillsSize = req_skills.size();
        int peopleSize = people.size();

        unordered_map<string, int> skill_index;
        for (int i = 0; i < req_skillsSize; ++i) {
            skill_index[req_skills[i]] = i;
        }

        vector<int> dp(1 << req_skillsSize, peopleSize);
        dp[0] = 0;

        vector<int> prev_skill(1 << req_skillsSize, 0);
        vector<int> prev_people(1 << req_skillsSize, 0);
        for (int i = 0; i < peopleSize; ++i) {
            int cur_skill = 0;

            for (string& skill : people[i]) {
                cur_skill |= (1 << skill_index[skill]);
            }

            for (int prev = 0; prev < (1 << req_skillsSize); prev++) {
                int comb = prev | cur_skill;
                if (dp[comb] > dp[prev] + 1) {
                    dp[comb] = dp[prev] + 1;
                    prev_skill[comb] = prev;
                    prev_people[comb] = i;
                }
            }
        }

        int i = (1 << req_skillsSize) - 1;
        while (i > 0) {
            retVal.push_back(prev_people[i]);
            i = prev_skill[i];
        }
        sort(retVal.begin(), retVal.end());

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> req_skills;
        vector<vector<string>> people;
    };
    vector<subject> testData{{{"java", "nodejs", "reactjs"}, {{"java"}, {"nodejs"}, {"nodejs", "reactjs"}}},
                             {{"algorithms", "math", "java", "reactjs", "csharp", "aws"},
                              {{"algorithms", "math", "java"},
                               {"algorithms", "math", "reactjs"},
                               {"java", "csharp", "aws"},
                               {"reactjs", "csharp"},
                               {"csharp", "math"},
                               {"aws", "java"}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: req_skills = ["java","nodejs","reactjs"], people = [["java"],["nodejs"],["nodejs","reactjs"]]
     *  Output: [0,2]
     *
     *  Input: req_skills = ["algorithms","math","java","reactjs","csharp","aws"],
     *  people = [["algorithms","math","java"],["algorithms","math","reactjs"],["java","csharp","aws"],
     *  ["reactjs","csharp"],["csharp","math"],["aws","java"]]
     *  Output: [1,2]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: req_skills = [";
        for (long unsigned int j = 0; j < testData[i].req_skills.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].req_skills[j] << "\"";
        }
        cout << "], people = [";
        for (long unsigned int j = 0; j < testData[i].people.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].people[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << "\"" << testData[i].people[j][k] << "\"";
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.smallestSufficientTeam(testData[i].req_skills, testData[i].people);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
