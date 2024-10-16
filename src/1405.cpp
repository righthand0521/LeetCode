#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    string longestDiverseString(int a, int b, int c) {
        string retVal;

        int curra = 0;
        int currb = 0;
        int currc = 0;
        int totalIterations = a + b + c;
        for (int i = 0; i < totalIterations; i++) {
            if (a >= b && a >= c && curra != 2) {
                retVal += 'a';
                a--;
                curra++;
                currb = 0;
                currc = 0;
            } else if (a > 0 && (currb == 2 || currc == 2)) {
                retVal += 'a';
                a--;
                curra++;
                currb = 0;
                currc = 0;
            } else if (b >= a && b >= c && currb != 2) {
                retVal += 'b';
                b--;
                currb++;
                curra = 0;
                currc = 0;
            } else if (b > 0 && (currc == 2 || curra == 2)) {
                retVal += 'b';
                b--;
                currb++;
                curra = 0;
                currc = 0;
            } else if (c >= a && c >= b && currc != 2) {
                retVal += 'c';
                c--;
                currc++;
                curra = 0;
                currb = 0;
            } else if (c > 0 && (curra == 2 || currb == 2)) {
                retVal += 'c';
                c--;
                currc++;
                curra = 0;
                currb = 0;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int a;
        int b;
        int c;
    };
    vector<subject> testData{{1, 1, 7}, {7, 1, 0}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: a = 1, b = 1, c = 7
     *  Output: "ccaccbcc"
     *
     *  Input: a = 7, b = 1, c = 0
     *  Output: "aabaa"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: a = " << testData[i].a << ", b = " << testData[i].b << ". c = " << testData[i].c << "\n";

        answer = cSolution.longestDiverseString(testData[i].a, testData[i].b, testData[i].c);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
