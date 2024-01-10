#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool isVowel(char c) {
        bool retVal = false;

        // The vowels are 'a', 'e', 'i', 'o', and 'u', and they can appear in both lower and upper cases
        if ((c == 'a') || (c == 'e') || (c == 'i') || (c == 'o') || (c == 'u')) {
            retVal = true;
        } else if ((c == 'A') || (c == 'E') || (c == 'I') || (c == 'O') || (c == 'U')) {
            retVal = true;
        }

        return retVal;
    }
    string reverseVowels(string s) {
        string retVal = "";

        int sSize = s.size();

        int left = 0;
        int right = sSize - 1;
        while (left < right) {
            while ((left < sSize) && (isVowel(s[left]) == false)) {
                ++left;
            }
            while ((right > 0) && (isVowel(s[right]) == false)) {
                --right;
            }

            if (left < right) {
                swap(s[left++], s[right--]);
            }
        }
        retVal = s;

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"hello"}, {"leetcode"}, {".,"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "hello"
     *  Output: "holle"
     *
     *  Input: s = "leetcode"
     *  Output: "leotcede"
     *
     *  Input: s = ".,"
     *  Output: ".,"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.reverseVowels(testData[i].s);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
