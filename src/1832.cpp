#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   public:
    bool checkIfPangram(string sentence) {
        bool retVal = false;

        unordered_set<char> seen(sentence.begin(), sentence.end());
        if (seen.size() == 26) {
            retVal = true;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string sentence;
    };
    vector<subject> testData{{{"thequickbrownfoxjumpsoverthelazydog"}}, {{"leetcode"}}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: sentence = \"" << testData[i].sentence << "\"\n";

        answer = cSolution.checkIfPangram(testData[i].sentence);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
