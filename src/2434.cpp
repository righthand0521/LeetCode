#include <algorithm>
#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    string robotWithString(string s) {
        string retVal;

        unordered_map<char, int> frequency;
        for (char c : s) {
            frequency[c]++;
        }
        stack<char> characterStack;
        char minCharacter = 'a';
        for (char c : s) {
            characterStack.emplace(c);
            frequency[c]--;

            while ((minCharacter != 'z') && (frequency[minCharacter] == 0)) {
                minCharacter++;
            }

            while ((characterStack.empty() == false) && (characterStack.top() <= minCharacter)) {
                retVal += characterStack.top();
                characterStack.pop();
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"zza"}, {"bac"}, {"bdda"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "zza"
     *  Output: "azz"
     *
     *  Input: s = "bac"
     *  Output: "abc"
     *
     *  Input: s = "bdda"
     *  Output: "addb"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: \"" << testData[i].s << "\"\n";

        answer = cSolution.robotWithString(testData[i].s);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
