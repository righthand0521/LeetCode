#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
// s consists of lowercase and uppercase English letters.
#define MAX_HASHTABLE (26)

   public:
    string greatestLetter(string s) {
        string retVal;

        unordered_set<char> hashTable(s.begin(), s.end());
        for (int i = (MAX_HASHTABLE - 1); i >= 0; --i) {
            if ((hashTable.count('a' + i) > 0) && (hashTable.count('A' + i) > 0)) {
                retVal = string(1, 'A' + i);
                break;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"lEeTcOdE"}, {"arRAzFif"}, {"AbCdEfGhIjK"}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.greatestLetter(testData[i].s);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
