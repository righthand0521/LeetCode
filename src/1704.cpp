#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool halvesAreAlike(string s) {
        bool retVal = true;

        string vowels = "aeiouAEIOU";

        int count = 0;
        int head = 0;
        int tail = s.size() - 1;
        while (head < tail) {
            if (vowels.find(s[head]) != string::npos) {
                ++count;
            }
            ++head;

            if (vowels.find(s[tail]) != string::npos) {
                --count;
            }
            --tail;
        }

        if (count != 0) {
            retVal = false;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"book"}, {"textbook"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "book"
     *  Output: true
     *
     *  Input: s = "textbook"
     *  Output: false
     */

    Solution cSolution;
    bool answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.halvesAreAlike(testData[i].s);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
