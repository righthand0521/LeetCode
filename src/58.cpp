#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int lengthOfLastWord(string s) {
        int retVal = 0;

        int sSize = s.size();
        for (int i = sSize - 1; i >= 0; --i) {
            if (s[i] != ' ') {
                ++retVal;
            } else {
                if (retVal != 0) {
                    break;
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"Hello World"}, {"   fly me   to   the moon  "}, {"luffy is still joyboy"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "Hello World"
     *  Output: 5
     *
     *  Input: s = "   fly me   to   the moon  "
     *  Output: 4
     *
     *  Input: s = "luffy is still joyboy"
     *  Output: 6
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.lengthOfLastWord(testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
