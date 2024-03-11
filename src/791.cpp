#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    int valSize = 26;  // 1 <= order.length <= 26

   public:
    string customSortString(string order, string s) {
        string retVal;

        int orderSize = order.size();
        vector<int> val(valSize, 0);
        for (int i = 0; i < orderSize; ++i) {
            int idx = order[i] - 'a';
            val[idx] = valSize - i;
        }

        sort(s.begin(), s.end(), [&](char c0, char c1) {
            // descending order
            return val[c0 - 'a'] > val[c1 - 'a'];
        });
        retVal = s;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string order;
        string s;
    };
    vector<subject> testData{{"cba", "abcd"}, {"bcafg", "abcd"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input:  order = "cba", s = "abcd"
     *  Output:  "cbad"
     *
     *  Input:  order = "bcafg", s = "abcd"
     *  Output:  "bcad"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: order = \"" << testData[i].order << "\", s = " << testData[i].s << "\n";

        answer = cSolution.customSortString(testData[i].order, testData[i].s);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
