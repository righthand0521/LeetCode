#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    string predictPartyVictory(string senate) {
        string retVal;

        queue<int> queueRadiant;
        queue<int> queueDire;

        int senateSize = senate.size();
        for (int i = 0; i < senateSize; ++i) {
            if (senate[i] == 'R') {
                queueRadiant.push(i);
            } else if (senate[i] == 'D') {
                queueDire.push(i);
            }
        }

        while ((queueRadiant.empty() == false) && (queueDire.empty() == false)) {
            auto idxRadiant = queueRadiant.front();
            auto idxDire = queueDire.front();

            if (idxRadiant < idxDire) {
                queueRadiant.push(idxRadiant + senateSize);
            } else if (idxRadiant > idxDire) {
                queueDire.push(idxDire + senateSize);
            }

            queueRadiant.pop();
            queueDire.pop();
        }

        if (queueRadiant.empty() == false) {
            retVal = "Radiant";
        } else if (queueDire.empty() == false) {
            retVal = "Dire";
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string senate;
    };
    vector<subject> testData{{"RD"}, {"RDD"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: senate = "RD"
     *  Output: "Radiant"
     *
     *  Input: senate = "RDD"
     *  Output: "Dire"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: senate = \"" << testData[i].senate << "\"\n";

        answer = cSolution.predictPartyVictory(testData[i].senate);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
