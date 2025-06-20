#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxDistance(string s, int k) {
        int retVal = 0;

        int latitude = 0;
        int longitude = 0;
        int sSize = s.size();
        for (int i = 0; i < sSize; i++) {
            switch (s[i]) {
                case 'N':
                    latitude++;
                    break;
                case 'S':
                    latitude--;
                    break;
                case 'E':
                    longitude++;
                    break;
                case 'W':
                    longitude--;
                    break;
            }
            retVal = max(retVal, min(abs(latitude) + abs(longitude) + k * 2, i + 1));
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
        int k;
    };
    vector<subject> testData{{"NWSE", 1}, {"NSWWEW", 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "NWSE", k = 1
     *  Output: 3
     *
     *  Input: s = "NSWWEW", k = 3
     *  Output: 6
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\", k = " << testData[i].k << "\n";

        answer = cSolution.maxDistance(testData[i].s, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
