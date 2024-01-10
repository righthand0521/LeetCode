#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int compress(vector<char>& chars) {
        int retVal = 0;

        int count = 1;
        int charsSize = chars.size();
        int i;
        for (i = 1; i < charsSize; ++i) {
            if (chars[i - 1] == chars[i]) {
                ++count;
                continue;
            }

            chars[retVal++] = chars[i - 1];
            if (count != 1) {
                string tmp = to_string(count);
                for (char c : tmp) {
                    chars[retVal++] = c;
                }
            }
            count = 1;
        }
        chars[retVal++] = chars[i - 1];
        if (count != 1) {
            string tmp = to_string(count);
            for (char c : tmp) {
                chars[retVal++] = c;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<char> chars;
    };
    vector<subject> testData{{{'a', 'a', 'b', 'b', 'c', 'c', 'c'}},
                             {{'a'}},
                             {{'a', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b'}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: chars = ["a","a","b","b","c","c","c"]
     *  Output: Return 6, and the first 6 characters of the input array should be: ["a","2","b","2","c","3"]
     *
     *  Input: chars = ["a"]
     *  Output: Return 1, and the first character of the input array should be: ["a"]
     *
     *  Input: chars = ["a","b","b","b","b","b","b","b","b","b","b","b","b"]
     *  Output: Return 4, and the first 4 characters of the input array should be: ["a","b","1","2"].
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: chars = [";
        for (long unsigned int j = 0; j < testData[i].chars.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].chars[j] << "\"";
        }
        cout << "]\n";

        answer = cSolution.compress(testData[i].chars);
        cout << "Output: " << answer << ", [";
        for (int j = 0; j < answer; ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].chars[j] << "\"";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
