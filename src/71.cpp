#include <algorithm>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
   public:
    string simplifyPath(string path) {
        string retVal = "";

        stack<string> stack;
        stringstream ss(path);
        string name;
        while (getline(ss, name, '/')) {
            if (name.length() == 0) {
                continue;
            }

            if (name.compare(".") == 0) {
                continue;
            } else if (name.compare("..") == 0) {
                if (stack.empty() == false) {
                    stack.pop();
                }
            } else {
                stack.push(name);
            }
        }

        while (stack.empty() == false) {
            retVal = "/" + stack.top() + retVal;
            stack.pop();
        }
        if (retVal.length() == 0) {
            retVal = "/";
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string path;
    };
    vector<subject> testData{{"/home/"}, {"/../"}, {"/home//foo/"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: path = "/home/"
     *  Output: "/home"
     *
     *  Input: path = "/../"
     *  Output: "/"
     *
     *  Input: path = "/home//foo/"
     *  Output: "/home/foo"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: path = \"" << testData[i].path << "\"\n";

        answer = cSolution.simplifyPath(testData[i].path);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
