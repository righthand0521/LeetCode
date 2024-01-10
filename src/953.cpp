#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// https://leetcode.com/problems/verifying-an-alien-dictionary/solutions/203185/java-c-python-mapping-to-normal-order/
class Solution {
// order.length == 26, All characters in words[i] and order are English lowercase letters.
#define MAX_ORDER_SIZE (26)
   public:
    bool isAlienSorted(vector<string>& words, string order) {
        bool retVal = false;

        int orderMap[MAX_ORDER_SIZE];
        for (int i = 0; i < MAX_ORDER_SIZE; ++i) {
            orderMap[order[i] - 'a'] = i + 'a';
        }

        for (string& str : words) {
            for (char& c : str) {
                c = orderMap[c - 'a'];
            }
        }
        retVal = is_sorted(words.begin(), words.end());

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> words;
        string order;
    };
    vector<subject> testData{{{"hello", "leetcode"}, "hlabcdefgijkmnopqrstuvwxyz"},
                             {{"word", "world", "row"}, "worldabcefghijkmnpqstuvxyz"},
                             {{"apple", "app"}, "abcdefghijklmnopqrstuvwxyz"}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: words = [";
        for (long unsigned int j = 0; j < testData[i].words.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].words[j];
        }
        cout << "], order = \"" << testData[i].order << "\"\n";

        answer = cSolution.isAlienSorted(testData[i].words, testData[i].order);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
