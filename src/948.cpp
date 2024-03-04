#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int bagOfTokensScore(vector<int>& tokens, int power) {
        int retVal = 0;

        int tokensSize = tokens.size();

        sort(tokens.begin(), tokens.end());
        int left = 0;
        int right = tokensSize - 1;
        while (left <= right) {
            if (power >= tokens[left]) {
                power -= tokens[left];
                left++;
                retVal++;
            } else if ((left < right) && (retVal > 0)) {
                power += tokens[right];
                right--;
                retVal--;
            } else {
                break;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> tokens;
        int power;
    };
    vector<subject> testData{{{100}, 50}, {{200, 100}, 150}, {{100, 200, 300, 400}, 200}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: tokens = [100], power = 50
     *  Output: 0
     *
     *  Input: tokens = [200,100], power = 150
     *  Output: 1
     *
     *  Input: tokens = [100,200,300,400], power = 200
     *  Output: 2
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: tokens = [";
        for (long unsigned int j = 0; j < testData[i].tokens.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].tokens[j];
        }
        cout << "], power = " << testData[i].power << "\n";

        answer = cSolution.bagOfTokensScore(testData[i].tokens, testData[i].power);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
