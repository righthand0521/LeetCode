#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minCost(string colors, vector<int>& neededTime) {
        int retVal = 0;

        int colorsSize = colors.size();

        int i = 0;
        while (i < colorsSize) {
            char previous = colors[i];
            int maxNeededTime = 0;
            int cost = 0;
            while ((i < colorsSize) && (colors[i] == previous)) {
                maxNeededTime = max(maxNeededTime, neededTime[i]);
                cost += neededTime[i];
                ++i;
            }
            retVal += (cost - maxNeededTime);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string colors;
        vector<int> neededTime;
    };
    vector<subject> testData{{"abaac", {1, 2, 3, 4, 5}}, {"abc", {1, 2, 3}}, {"aabaa", {1, 2, 3, 4, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: colors = "abaac", neededTime = [1,2,3,4,5]
     *  Output: 3
     *
     *  Input: colors = "abc", neededTime = [1,2,3]
     *  Output: 0
     *
     *  Input: colors = "aabaa", neededTime = [1,2,3,4,1]
     *  Output: 2
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: colors = \"" << testData[i].colors << "\"";
        cout << ", neededTime = [";
        for (long unsigned int j = 0; j < testData[i].neededTime.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].neededTime[j];
        }
        cout << "]\n";

        answer = cSolution.minCost(testData[i].colors, testData[i].neededTime);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
