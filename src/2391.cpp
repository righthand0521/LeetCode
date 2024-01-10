#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int garbageCollection(vector<string>& garbage, vector<int>& travel) {
        int retVal = 0;

        int travelSize = travel.size();
        vector<int> travelPrefixSum((travelSize + 1), 0);
        for (int i = 0; i < travelSize; ++i) {
            travelPrefixSum[i + 1] = travelPrefixSum[i] + travel[i];
        }

        // garbage[i] consists only of the characters 'M', 'P' and 'G'
        int garbageType = 4;
        vector<int> lastGarbage(garbageType, 0);
        int garbageSize = garbage.size();
        for (int i = 0; i < garbageSize; ++i) {
            for (char c : garbage[i]) {
                if (c == 'M') {
                    lastGarbage[1] = i;
                } else if (c == 'P') {
                    lastGarbage[2] = i;
                } else if (c == 'G') {
                    lastGarbage[3] = i;
                }
                retVal += 1;
            }
        }

        for (int i = 0; i < garbageType; ++i) {
            retVal += travelPrefixSum[lastGarbage[i]];
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> garbage;
        vector<int> travel;
    };
    vector<subject> testData{{{"G", "P", "GP", "GG"}, {2, 4, 3}}, {{"MMM", "PGM", "GP"}, {3, 10}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: garbage = ["G","P","GP","GG"], travel = [2,4,3]
     *  Output: 21
     *
     *  Input: garbage = ["MMM","PGM","GP"], travel = [3,10]
     *  Output: 37
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: garbage = [";
        for (long unsigned int j = 0; j < testData[i].garbage.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].garbage[j] << "\"";
        }
        cout << "], travel = [";
        for (long unsigned int j = 0; j < testData[i].travel.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].travel[j];
        }
        cout << "]\n";

        answer = cSolution.garbageCollection(testData[i].garbage, testData[i].travel);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
