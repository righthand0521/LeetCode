#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    long long calculate(string x, string s, int limit) {
        long long retVal = 0;

        int xSize = x.size();
        int sSize = s.size();
        if (xSize < sSize) {
            return retVal;
        } else if (xSize == sSize) {
            if (x >= s) {
                retVal = 1;
            }
            return retVal;
        }

        string suffix = x.substr(xSize - sSize, sSize);

        int preLen = xSize - sSize;
        for (int i = 0; i < preLen; i++) {
            if (limit < (x[i] - '0')) {
                retVal += (long)pow(limit + 1, preLen - i);
                return retVal;
            }
            retVal += (long)(x[i] - '0') * (long)pow(limit + 1, preLen - 1 - i);
        }

        if (suffix >= s) {
            retVal++;
        }

        return retVal;
    }

   public:
    long long numberOfPowerfulInt(long long start, long long finish, int limit, string s) {
        long long retVal = 0;

        string startString = to_string(start - 1);
        string finishString = to_string(finish);
        retVal = calculate(finishString, s, limit) - calculate(startString, s, limit);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        long long start;
        long long finish;
        int limit;
        string s;
    };
    vector<subject> testData{{1, 6000, 4, "124"}, {15, 215, 6, "10"}, {1000, 2000, 4, "3000"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: start = 1, finish = 6000, limit = 4, s = "124"
     *  Output: 5
     *
     *  Input: start = 15, finish = 215, limit = 6, s = "10"
     *  Output: 2
     *
     *  Input: start = 1000, finish = 2000, limit = 4, s = "3000"
     *  Output: 0
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: start = " << testData[i].start;
        cout << ", finish = " << testData[i].finish;
        cout << ", limit = " << testData[i].limit;
        cout << ", s = \"" << testData[i].s << "\"\n";

        answer = cSolution.numberOfPowerfulInt(testData[i].start, testData[i].finish, testData[i].limit, testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
