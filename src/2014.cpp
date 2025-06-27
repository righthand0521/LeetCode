#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   private:
    int letterSize = 26;  // s consists of lowercase English letters.

    bool isKRepeatedSubsequence(const string& s, const string& t, int k) {
        bool retVal = false;

        int tSize = t.size();
        int pos = 0;
        int matched = 0;
        for (char ch : s) {
            if (ch != t[pos]) {
                continue;
            }

            pos++;
            if (pos != tSize) {
                continue;
            }

            pos = 0;
            matched++;
            if (matched == k) {
                retVal = true;
                break;
            }
        }

        return retVal;
    }

   public:
    string longestSubsequenceRepeatedK(string s, int k) {
        string retVal = "";

        vector<int> frequency(letterSize);
        for (char ch : s) {
            frequency[ch - 'a']++;
        }

        vector<char> candidate;
        for (int i = (letterSize - 1); i >= 0; i--) {
            if (frequency[i] >= k) {
                candidate.push_back('a' + i);
            }
        }

        queue<string> candidateQueue;
        for (char ch : candidate) {
            candidateQueue.push(string(1, ch));
        }

        while (candidateQueue.empty() == false) {
            string curr = candidateQueue.front();
            candidateQueue.pop();
            if (curr.size() > retVal.size()) {
                retVal = curr;
            }

            // generate the next candidate string
            for (char ch : candidate) {
                string next = curr + ch;
                if (isKRepeatedSubsequence(s, next, k) == true) {
                    candidateQueue.push(next);
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
        int k;
    };
    vector<subject> testData{{"letsleetcode", 2}, {"bb", 2}, {"ab", 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "letsleetcode", k = 2
     *  Output: "let"
     *
     *  Input: s = "bb", k = 2
     *  Output: "b"
     *
     *  Input: s = "ab", k = 2
     *  Output: ""
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\", k = " << testData[i].k << "\n";

        answer = cSolution.longestSubsequenceRepeatedK(testData[i].s, testData[i].k);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
