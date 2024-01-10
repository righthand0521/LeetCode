#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int matchPlayersAndTrainers(vector<int>& players, vector<int>& trainers) {
        int retVal = 0;

        sort(players.begin(), players.end());
        int playersSize = players.size();
        int playersIdx = 0;

        sort(trainers.begin(), trainers.end());
        int trainersSize = trainers.size();
        int trainersIdx = 0;

        while ((playersIdx < playersSize) && (trainersIdx < trainersSize)) {
            while ((trainersIdx < trainersSize) && (players[playersIdx] > trainers[trainersIdx])) {
                ++trainersIdx;
            }

            if (trainersIdx < trainersSize) {
                ++retVal;
            }

            ++playersIdx;
            ++trainersIdx;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> players;
        vector<int> trainers;
    };
    vector<subject> testData{{{4, 7, 9}, {8, 2, 5, 8}}, {{1, 1, 1}, {10}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: players = [4,7,9], trainers = [8,2,5,8]
     *  Output: 2
     *
     *  Input: players = [1,1,1], trainers = [10]
     *  Output: 1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: players = [";
        for (long unsigned int j = 0; j < testData[i].players.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].players[j];
        }
        cout << "], trainers = [";
        for (long unsigned int j = 0; j < testData[i].trainers.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].trainers[j];
        }
        cout << "]\n";

        answer = cSolution.matchPlayersAndTrainers(testData[i].players, testData[i].trainers);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
