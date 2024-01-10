#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
#define STRONG_PASSWORD_LENGTH (8)
#define STRONG_PASSWORD_LOWERCASE_BIT (0)
#define STRONG_PASSWORD_UPPERCASE_BIT (1)
#define STRONG_PASSWORD_DIGIT_BIT (2)
#define STRONG_PASSWORD_SPECIAL_BIT (3)

   public:
    bool strongPasswordCheckerII(string password) {
        bool retVal = false;

        int len = password.length();
        if (len < STRONG_PASSWORD_LENGTH) {
            return retVal;
        }

        int resultBit = 0;
        unordered_set<char> specialCharacters = {'!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '+'};
        for (int i = 0; i < len; ++i) {
            if (password[i] == password[i + 1]) {
                return retVal;
            }

            if (islower(password[i])) {
                resultBit |= (1 << STRONG_PASSWORD_LOWERCASE_BIT);
            } else if (isupper(password[i])) {
                resultBit |= (1 << STRONG_PASSWORD_UPPERCASE_BIT);
            } else if (isdigit(password[i])) {
                resultBit |= (1 << STRONG_PASSWORD_DIGIT_BIT);
            } else if (specialCharacters.count(password[i])) {
                resultBit |= (1 << STRONG_PASSWORD_SPECIAL_BIT);
            }
        }
        if (resultBit == ((1 << STRONG_PASSWORD_LOWERCASE_BIT) | (1 << STRONG_PASSWORD_UPPERCASE_BIT) |
                          (1 << STRONG_PASSWORD_DIGIT_BIT) | (1 << STRONG_PASSWORD_SPECIAL_BIT))) {
            retVal = true;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string password;
    };
    vector<subject> testData{{"IloveLe3tcode!"}, {"Me+You--IsMyDream"}, {"1aB!"}, {"aA0!bB1@@3rbHkB8Puvl"}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    bool answer = false;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: password = \"" << testData[i].password << "\"\n";

        answer = cSolution.strongPasswordCheckerII(testData[i].password);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
