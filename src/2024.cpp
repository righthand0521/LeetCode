#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxConsecutiveAnswers(string answerKey, int k) {
        int retVal = 0;

        // answerKey[i] is either 'T' or 'F'
#define MAX_RECORD (26)
        vector<int> Record(MAX_RECORD, 0);

        int maxRecord = 0;
        int answerKeySize = answerKey.length();
        int left = 0;
        int right = 0;
        while (right < answerKeySize) {
            Record[answerKey[right] - 'A']++;

            maxRecord = max(maxRecord, Record[answerKey[right] - 'A']);
            if (right - left + 1 - maxRecord > k) {
                Record[answerKey[left] - 'A']--;
                left++;
            }

            right++;
        }
        retVal = right - left;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string answerKey;
        int k;
    };
    vector<subject> testData{{"TTFF", 2}, {"TFFT", 1}, {"TTFTTFTT", 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: answerKey = "TTFF", k = 2
     *  Output: 4
     *
     *  Input: answerKey = "TFFT", k = 1
     *  Output: 3
     *
     *  Input: answerKey = "TTFTTFTT", k = 1
     *  Output: 5
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: answerKey = \"" << testData[i].answerKey << "\", k = " << testData[i].k << "\n";

        answer = cSolution.maxConsecutiveAnswers(testData[i].answerKey, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
