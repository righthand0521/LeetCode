#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        char retVal = letters[0];

        for (auto c : letters) {
            if (c > target) {
                retVal = c;
                break;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<char> letters;
        char target;
    };
    vector<subject> testData{{{'c', 'f', 'j'}, 'a'}, {{'c', 'f', 'j'}, 'c'}, {{'x', 'x', 'y', 'y'}, 'z'}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: letters = ["c","f","j"], target = "a"
     *  Output: "c"
     *
     *  Input: letters = ["c","f","j"], target = "c"
     *  Output: "f"
     *
     *  Input: letters = ["x","x","y","y"], target = "z"
     *  Output: "x"
     */

    Solution cSolution;
    char answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: letters = [";
        for (long unsigned int j = 0; j < testData[i].letters.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].letters[j] << "\"";
        }
        cout << "], target = \"" << testData[i].target << "\"\n";

        answer = cSolution.nextGreatestLetter(testData[i].letters, testData[i].target);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
