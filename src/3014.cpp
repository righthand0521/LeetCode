#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minimumPushes(string word) {
        int retVal = 0;

        int wordSize = word.size();
        int quotient = wordSize / 8;
        int remainder = wordSize % 8;
        retVal = ((quotient << 2) + remainder) * (quotient + 1);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string word;
    };
    vector<subject> testData{{"abcde"}, {"xycdefghij"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: word = "abcde"
     *  Output: 5
     *
     *  Input: word = "xycdefghij"
     *  Output: 12
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: word = \"" << testData[i].word << "\"\n";

        answer = cSolution.minimumPushes(testData[i].word);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
