#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    string defangIPaddr(string address) {
        string retVal;

        for (auto c : address) {
            if (c == '.') {
                retVal += "[.]";
            } else {
                retVal += c;
            }
        }

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        string address;
    };
    vector<subject> testData{{"1.1.1.1"}, {"255.100.50.0"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: address = "1.1.1.1"
     *  Output: "1[.]1[.]1[.]1"
     *
     *  Input: address = "255.100.50.0"
     *  Output: "255[.]100[.]50[.]0"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: address = \"" << testData[i].address << "\"\n";

        answer = cSolution.defangIPaddr(testData[i].address);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
