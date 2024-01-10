#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    string orderlyQueue(string s, int k) {
        string retVal = s;

        // k>=2: Bubble Sort Concept? it could get the optimal solution(ascending order)
        if (k > 1) {
            sort(retVal.begin(), retVal.end());
            return retVal;
        }

        // k = 1: rotate the whole string to return the lexicographically smallest string
        for (long unsigned int i = 1; i < s.length(); ++i) {
            retVal = min(retVal, s.substr(i) + s.substr(0, i));
        }

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        string s;
        int k;
    };
    vector<subject> testData{{"cba", 1}, {"baaca", 3}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\", k = " << testData[i].k << "\n";

        answer = cSolution.orderlyQueue(testData[i].s, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
