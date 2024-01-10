#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   public:
    bool isPathCrossing(string path) {
        bool retVal = false;

        unordered_map<char, pair<int, int>> moves;
        moves['N'] = {0, 1};
        moves['S'] = {0, -1};
        moves['W'] = {-1, 0};
        moves['E'] = {1, 0};

        unordered_set<string> visited;

        int x = 0;
        int y = 0;
        string pointsHash = to_string(x) + "," + to_string(y);
        visited.insert(pointsHash);

        for (char direction : path) {
            x += moves[direction].first;
            y += moves[direction].second;
            string pointsHash = to_string(x) + "," + to_string(y);
            if (visited.find(pointsHash) != visited.end()) {
                retVal = true;
                break;
            }
            visited.insert(pointsHash);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string path;
    };
    vector<subject> testData{{"NES"}, {"NESWW"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: path = "NES"
     *  Output: false
     *
     *  Input: path = "NESWW"
     *  Output: true
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: path = \"" << testData[i].path << "\"\n";

        answer = cSolution.isPathCrossing(testData[i].path);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
