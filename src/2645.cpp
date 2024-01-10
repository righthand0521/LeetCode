#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    // https://leetcode.com/problems/minimum-additions-to-make-valid-string/solutions/3421831/java-c-python-easy-and-concise-with-explanation/
    int addMinimum(string word) {
        int retVal = 0;

        int count = 0;
        char previousChar = 'z';
        for (auto c : word) {
            count += (c <= previousChar);
            previousChar = c;
        }
        retVal = 3 * count - word.size();

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        string word;
    };
    vector<subject> testData{{"b"}, {"aaa"}, {"abc"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: word = "b"
     *  Output: 2
     *
     *  Input: word = "aaa"
     *  Output: 6
     *
     *  Input: word = "abc"
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: word = \"" << testData[i].word << "\"\n";

        answer = cSolution.addMinimum(testData[i].word);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
