#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<string> sortPeople(vector<string>& names, vector<int>& heights) {
        vector<string> retVal;

        int namesSize = names.size();
        int id[namesSize];
        iota(id, id + namesSize, 0);
        sort(id, id + namesSize, [&](const auto& x, const auto& y) {
            // descending order
            return (heights[x] > heights[y]);
        });

        for (int i = 0; i < namesSize; ++i) {
            retVal.emplace_back(names[id[i]]);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> names;
        vector<int> heights;
    };
    vector<subject> testData{{{"Mary", "John", "Emma"}, {180, 165, 170}}, {{"Alice", "Bob", "Bob"}, {155, 185, 150}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: names = ["Mary","John","Emma"], heights = [180,165,170]
     *  Output: ["Mary","Emma","John"]
     *
     *  Input: names = ["Alice","Bob","Bob"], heights = [155,185,150]
     *  Output: ["Bob","Alice","Bob"]
     */

    Solution cSolution;
    vector<string> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: names = [";
        for (long unsigned int j = 0; j < testData[i].names.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].names[j] << "\"";
        }
        cout << "], heights = [";
        for (long unsigned int j = 0; j < testData[i].heights.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].heights[j];
        }
        cout << "]\n";

        answer = cSolution.sortPeople(testData[i].names, testData[i].heights);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << answer[j] << "\"";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
