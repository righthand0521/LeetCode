#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    string pushDominoes(string dominoes) {
        string retVal = dominoes;

        char left = 'L';
        int dominoesSize = dominoes.size();
        int i = 0;
        while (i < dominoesSize) {
            int j = i;
            while ((j < dominoesSize) && (retVal[j] == '.')) {
                j++;
            }

            char right = (j < dominoesSize) ? (retVal[j]) : ('R');
            if (left == right) {
                while (i < j) {
                    retVal[i++] = right;
                }
            } else if (left == 'R' && right == 'L') {
                int k = j - 1;
                while (i < k) {
                    retVal[i++] = 'R';
                    retVal[k--] = 'L';
                }
            }

            left = right;
            i = j + 1;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string dominoes;
    };
    vector<subject> testData{{"RR.L"}, {".L.R...LR..L.."}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: dominoes = "RR.L"
     *  Output: "RR.L"
     *
     *  Input: dominoes = ".L.R...LR..L.."
     *  Output: "LL.RR.LLRRLL.."
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: dominoes = \"" << testData[i].dominoes << "\"\n";

        answer = cSolution.pushDominoes(testData[i].dominoes);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
