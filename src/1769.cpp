#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> minOperations(string boxes) {
        vector<int> retVal;

        int boxesSize = boxes.size();
        retVal.assign(boxesSize, 0);

        int ballsToLeft = 0;
        int movesToLeft = 0;
        int ballsToRight = 0;
        int movesToRight = 0;
        for (int i = 0; i < boxesSize; i++) {
            // Left pass
            retVal[i] += movesToLeft;
            ballsToLeft += boxes[i] - '0';
            movesToLeft += ballsToLeft;

            // Right pass
            int j = boxesSize - 1 - i;
            retVal[j] += movesToRight;
            ballsToRight += boxes[j] - '0';
            movesToRight += ballsToRight;
        }

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        string boxes;
    };
    vector<subject> testData{{"110"}, {"001011"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: boxes = "110"
     *  Output: [1,1,3]
     *
     *  Input: boxes = "001011"
     *  Output: [11,8,5,4,3,4]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: boxes = \"" << testData[i].boxes << "\"\n";

        answer = cSolution.minOperations(testData[i].boxes);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
