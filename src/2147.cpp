#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
#define MODULO (int)(1e9 + 7)
   public:
    int numberOfWays(string corridor) {
        int retVal = 0;

        int corridorSize = corridor.size();

        long answer = 1;
        int count = 0;
        int previous = -1;
        for (int i = 0; i < corridorSize; ++i) {
            if (corridor[i] == 'S') {
                count++;

                if ((count >= 3) && (count % 2 == 1)) {
                    answer = (answer * (i - previous)) % MODULO;
                }

                previous = i;
            }
        }

        if ((count < 2) || (count % 2 == 1)) {
            answer = 0;
        }
        retVal = answer;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string corridor;
    };
    vector<subject> testData{{"SSPPSPS"}, {"PPSPSP"}, {"S"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: corridor = "SSPPSPS"
     *  Output: 3
     *
     *  Input: corridor = "PPSPSP"
     *  Output: 1
     *
     *  Input: corridor = "S"
     *  Output: 0
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: corridor = \"" << testData[i].corridor << "\"\n";

        answer = cSolution.numberOfWays(testData[i].corridor);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
