#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool isPalindrome(string s) {
        bool retVal = true;

        // A phrase is a palindrome if, after converting all uppercase letters into lowercase letters
        // and removing all non - alphanumeric characters, it reads the same forward and backward.
        // Alphanumeric characters include letters and numbers.
        string palindrome;
        for (char ch : s) {
            if (isalnum(ch)) {
                palindrome += tolower(ch);
            }
        }

        int head = 0;
        int tail = palindrome.size() - 1;
        while (head < tail) {
            if (palindrome[head] != palindrome[tail]) {
                retVal = false;
                break;
            }
            ++head;
            --tail;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"A man, a plan, a canal: Panama"}, {"race a car"}, {" "}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "A man, a plan, a canal: Panama"
     *  Output: true
     *
     *  Input: s = "race a car"
     *  Output: false
     *
     *  Input: s = " "
     *  Output: true
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.isPalindrome(testData[i].s);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
