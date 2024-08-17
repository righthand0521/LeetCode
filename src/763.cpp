#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    int letters = 26;  // s consists of lowercase English letters.

   public:
    vector<int> partitionLabels(string s) {
        vector<int> retVal;

        vector<int> last(letters, 0);
        int sSize = s.size();
        for (int i = 0; i < sSize; ++i) {
            last[s[i] - 'a'] = i;
        }

        int start = 0;
        int end = 0;
        for (int i = 0; i < sSize; ++i) {
            end = max(end, last[s[i] - 'a']);
            if (i == end) {
                retVal.emplace_back(i - start + 1);
                start = i + 1;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"ababcbacadefegdehijhklij"}, {"eccbbbbdec"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "ababcbacadefegdehijhklij"
     *  Output: [9,7,8]
     *
     *  Input: s = "eccbbbbdec"
     *  Output: [10]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.partitionLabels(testData[i].s);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
