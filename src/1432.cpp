#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    static void replace(string& s, char x, char y) {
        for (char& digit : s) {
            if (digit == x) {
                digit = y;
            }
        }
    }

   public:
    int maxDiff(int num) {
        int retVal = 0;

        // Find a high position and replace it with 9.
        string maxNum = to_string(num);
        for (char digit : maxNum) {
            if (digit != '9') {
                replace(maxNum, digit, '9');
                break;
            }
        }

        // Replace the most significant bit with 1
        // Or find a high-order digit that is not equal to the highest digit and  replace it with 0.
        string minNum = to_string(num);
        int minNumSize = minNum.size();
        for (int i = 0; i < minNumSize; ++i) {
            char digit = minNum[i];
            if (i == 0) {
                if (digit != '1') {
                    replace(minNum, digit, '1');
                    break;
                }
            } else {
                if (digit != '0' && digit != minNum[0]) {
                    replace(minNum, digit, '0');
                    break;
                }
            }
        }

        retVal = stoi(maxNum) - stoi(minNum);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int num;
    };
    vector<subject> testData{{555}, {9}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: num = 555
     *  Output: 888
     *
     *  Input: num = 9
     *  Output: 8
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: num = " << testData[i].num << "\n";

        answer = cSolution.maxDiff(testData[i].num);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
