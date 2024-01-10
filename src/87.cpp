#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   private:
    unordered_map<string, bool> mem;

   public:
    // https://leetcode.com/problems/scramble-string/solutions/1923664/92faster-recursive-Solution-unordered_map-Optimization/
    bool isScramble(string s1, string s2) {
        bool retVal = false;

        if (s1.size() <= 1) {
            retVal = (s1[0] == s2[0]);
            return retVal;
        }

        if (mem.find(s1 + s2) != mem.end()) {
            retVal = mem[s1 + s2];
            return retVal;
        }

        string t1 = s1;
        string t2 = s2;
        sort(t1.begin(), t1.end());
        sort(t2.begin(), t2.end());
        if (t1 != t2) {
            mem[s1 + s2] = retVal;
            return retVal;
        }

        int s1Size = s1.size();
        for (int i = 1; i < s1Size; ++i) {
            string x = s1.substr(0, i);
            string y = s1.substr(i, s1.size() - i);
            if (((isScramble(s2.substr(0, x.size()), x)) && (isScramble(s2.substr(x.size(), y.size()), y))) ||
                ((isScramble(s2.substr(0, y.size()), y)) && (isScramble(s2.substr(y.size(), x.size()), x)))) {
                retVal = true;
                mem[s1 + s2] = retVal;
                return retVal;
            }
        }
        mem[s1 + s2] = retVal;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s1;
        string s2;
    };
    vector<subject> testData{{"great", "rgeat"}, {"abcde", "caebd"}, {"a", "a"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s1 = "great", s2 = "rgeat"
     *  Output: true
     *
     *  Input: s1 = "abcde", s2 = "caebd"
     *  Output: false
     *
     *  Input: s1 = "a", s2 = "a"
     *  Output: true
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s1 = \"" << testData[i].s1 << "\", s2 = \"" << testData[i].s2 << "\"\n";

        answer = cSolution.isScramble(testData[i].s1, testData[i].s2);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
