#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    string reverseWords(string s) {
        string retVal = s;

        int retValSize = retVal.size();

        int left = 0;
        int right = 0;
        for (int i = 0; i <= retValSize; ++i) {
            if ((retVal[i] != ' ') && (retVal[i] != '\0')) {
                continue;
            }

            right = i - 1;
            while (left < right) {
                char tmp = retVal[left];
                retVal[left++] = retVal[right];
                retVal[right--] = tmp;
            }
            left = i + 1;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"Let's take LeetCode contest"}, {"God Ding"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "Let's take LeetCode contest"
     *  Output: "s'teL ekat edoCteeL tsetnoc"
     *
     *  Input: s = "God Ding"
     *  Output: "doG gniD"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.reverseWords(testData[i].s);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
