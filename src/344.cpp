#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    void reverseString(vector<char>& s) {
        //
        reverse(s.begin(), s.end());
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<char> s;
    };
    vector<subject> testData{{{'h', 'e', 'l', 'l', 'o'}}, {{'H', 'a', 'n', 'n', 'a', 'h'}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = ["h","e","l","l","o"]
     *  Output: ["o","l","l","e","h"]
     *
     *  Input: s = ["H","a","n","n","a","h"]
     *  Output: ["h","a","n","n","a","H"]
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = [";
        for (long unsigned int j = 0; j < testData[i].s.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].s[j] << "\"";
        }
        cout << "]\n";

        cSolution.reverseString(testData[i].s);
        cout << "Output: [";
        for (long unsigned int j = 0; j < testData[i].s.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].s[j] << "\"";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
