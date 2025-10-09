#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    long long minTime(vector<int>& skill, vector<int>& mana) {
        long long retVal = 0;

        int skillSize = skill.size();
        int manaSize = mana.size();

        vector<long long> times(skillSize);
        for (int j = 0; j < manaSize; j++) {
            long long currentTime = 0;
            for (int i = 0; i < skillSize; i++) {
                currentTime = max(currentTime, times[i]) + skill[i] * mana[j];
            }
            times[skillSize - 1] = currentTime;
            for (int i = skillSize - 2; i >= 0; i--) {
                times[i] = times[i + 1] - skill[i + 1] * mana[j];
            }
        }
        retVal = times[skillSize - 1];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> skill;
        vector<int> mana;
    };
    vector<subject> testData{{{1, 5, 2, 4}, {5, 1, 4, 2}}, {{1, 1, 1}, {1, 1, 1}}, {{1, 2, 3, 4}, {1, 2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: skill = [1,5,2,4], mana = [5,1,4,2]
     *  Output: 110
     *
     *  Input: skill = [1,1,1], mana = [1,1,1]
     *  Output: 5
     *
     *  Input: skill = [1,2,3,4], mana = [1,2]
     *  Output: 21
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: skill = [";
        for (long unsigned int j = 0; j < testData[i].skill.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].skill[j];
        }
        cout << "], mana = [";
        for (long unsigned int j = 0; j < testData[i].mana.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].mana[j];
        }
        cout << "]\n";

        answer = cSolution.minTime(testData[i].skill, testData[i].mana);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
