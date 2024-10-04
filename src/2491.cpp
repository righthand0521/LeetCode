#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    long long dividePlayers(vector<int>& skill) {
        long long retVal = -1;

        int skillSize = skill.size();

        int totalSkill = 0;
        vector<int> skillFrequency(1001, 0);  // 1 <= skill[i] <= 1000
        for (int playerSkill : skill) {
            totalSkill += playerSkill;
            skillFrequency[playerSkill]++;
        }
        if (totalSkill % (skillSize / 2) != 0) {
            return retVal;
        }

        int targetTeamSkill = totalSkill / (skillSize / 2);
        long long totalChemistry = 0;
        for (int playerSkill : skill) {
            int partnerSkill = targetTeamSkill - playerSkill;
            if (skillFrequency[partnerSkill] == 0) {
                return retVal;
            }

            totalChemistry += (long long)playerSkill * (long long)partnerSkill;
            skillFrequency[partnerSkill]--;
        }
        retVal = totalChemistry / 2;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> skill;
    };
    vector<subject> testData{{{3, 2, 5, 1, 3, 4}}, {{3, 4}}, {{1, 1, 2, 3}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: skill = [3,2,5,1,3,4]
     *  Output: 22
     *
     *  Input: skill = [3,4]
     *  Output: 12
     *
     *  Input: skill = [1,1,2,3]
     *  Output: -1
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: skill = [";
        for (long unsigned int j = 0; j < testData[i].skill.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].skill[j];
        }
        cout << "]\n";

        answer = cSolution.dividePlayers(testData[i].skill);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
