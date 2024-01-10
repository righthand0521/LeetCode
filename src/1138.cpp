#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    string alphabetBoardPath(string target) {
        string retVal;

        vector<int> src(2, 0);
        vector<int> dest(2, 0);
        for (auto c : target) {
            dest[0] = (c - 'a') / 5;
            dest[1] = (c - 'a') % 5;

            int rowMove = dest[0] - src[0];
            int colMove = dest[1] - src[1];

            /* Because Address of 'z'
             *  Notice that moving down and moving right, may move into a square that doesn't exist.
             *  To avoid this, we put L U before R D.
             *
             *  You may return any path that does so.
             */
            if (rowMove < 0) {
                retVal += string(-rowMove, 'U');
            }
            if (colMove < 0) {
                retVal += string(-colMove, 'L');
            }
            if (rowMove > 0) {
                retVal += string(rowMove, 'D');
            }
            if (colMove > 0) {
                retVal += string(colMove, 'R');
            }
            retVal += '!';

            src = dest;
        }

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        string target;
    };
    vector<subject> testData{{"leet"}, {"code"}, {"zdz"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: target = "leet"
     *  Output: "DDR!UURRR!!DDD!"
     *
     *  Input: target = "code"
     *  Output: "RR!DDRR!UUL!R!"
     *
     *  Input: target = "zdz"
     *  Output: "DDDDD!UUUUURRR!DDDDLLLD!"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: target = \"" << testData[i].target << "\"\n";

        answer = cSolution.alphabetBoardPath(testData[i].target);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
