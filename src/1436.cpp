#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   public:
    string destCity(vector<vector<string>>& paths) {
        string retVal;

        int pathsSize = paths.size();

        unordered_set<string> outgoing;
        for (int i = 0; i < pathsSize; ++i) {
            outgoing.insert(paths[i][0]);
        }

        for (int i = 0; i < pathsSize; ++i) {
            string cityB = paths[i][1];
            if (outgoing.count(cityB) == 0) {
                retVal = cityB;
                break;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<string>> paths;
    };
    vector<subject> testData{{{{"London", "New York"}, {"New York", "Lima"}, {"Lima", "Sao Paulo"}}},
                             {{{"B", "C"}, {"D", "B"}, {"C", "A"}}},
                             {{{"A", "Z"}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: paths = [["London","New York"],["New York","Lima"],["Lima","Sao Paulo"]]
     *  Output: "Sao Paulo"
     *
     *  Input: paths = [["B","C"],["D","B"],["C","A"]]
     *  Output: "A"
     *
     *  Input: paths = [["A","Z"]]
     *  Output: "Z"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: paths = [";
        for (long unsigned int j = 0; j < testData[i].paths.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].paths[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << "\"" << testData[i].paths[j][k] << "\"";
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.destCity(testData[i].paths);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
