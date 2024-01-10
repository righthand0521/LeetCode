#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    string blank(int n) {
        string retVal = string(n, ' ');

        return retVal;
    }
    string join(vector<string>& words, int left, int right, string sep) {
        string retVal = words[left];

        for (int i = left + 1; i < right; ++i) {
            retVal += sep + words[i];
        }

        return retVal;
    }
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> retVal;

        int wordsSize = words.size();
        int right = 0;
        while (true) {
            int left = right;
            int sumLen = 0;

            while ((right < wordsSize) && (sumLen + (int)(words[right].length()) + right - left <= maxWidth)) {
                sumLen += words[right++].length();
            }

            if (right == wordsSize) {
                string s = join(words, left, wordsSize, " ");
                retVal.emplace_back(s + blank(maxWidth - s.length()));
                return retVal;
            }

            int numSpaces = maxWidth - sumLen;
            int numWords = right - left;
            if (numWords == 1) {
                retVal.emplace_back(words[left] + blank(numSpaces));
                continue;
            }

            int avgSpaces = numSpaces / (numWords - 1);
            int extraSpaces = numSpaces % (numWords - 1);
            string s1 = join(words, left, left + extraSpaces + 1, blank(avgSpaces + 1));
            string s2 = join(words, left + extraSpaces + 1, right, blank(avgSpaces));
            retVal.emplace_back(s1 + blank(avgSpaces) + s2);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> words;
        int maxWidth;
    };
    vector<subject> testData{{{"This", "is", "an", "example", "of", "text", "justification."}, 16},
                             {{"What", "must", "be", "acknowledgment", "shall", "be"}, 16},
                             {{"Science", "is", "what", "we", "understand", "well", "enough", "to", "explain", "to",
                               "a", "computer.", "Art", "is", "everything", "else", "we", "do"},
                              20}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: words = ["This", "is", "an", "example", "of", "text", "justification."], maxWidth = 16
     *  Output:
     *  [
     *     "This    is    an",
     *     "example  of text",
     *     "justification.  "
     *  ]
     *
     *  Input: words = ["What","must","be","acknowledgment","shall","be"], maxWidth = 16
     *  Output:
     *  [
     *    "What   must   be",
     *    "acknowledgment  ",
     *    "shall be        "
     *  ]
     *
     *  Input: words = ["Science","is","what","we","understand","well","enough","to","explain","to","a","computer.",
     *  "Art","is","everything","else","we","do"], maxWidth = 20
     *  Output:
     *  [
     *    "Science  is  what we",
     *    "understand      well",
     *    "enough to explain to",
     *    "a  computer.  Art is",
     *    "everything  else  we",
     *    "do                  "
     *  ]
     */

    Solution cSolution;
    vector<string> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: words = [";
        for (long unsigned int j = 0; j < testData[i].words.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].words[j] << "\"";
        }
        cout << "], maxWidth = " << testData[i].maxWidth << "\n";

        answer = cSolution.fullJustify(testData[i].words, testData[i].maxWidth);
        cout << "Output:\n[\n";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",\n") << "  \"" << answer[j] << "\"";
        }
        cout << "\n]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
