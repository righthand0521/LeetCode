#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int countCollisions(string directions) {
        int retVal = 0;

        // https://leetcode.cn/problems/count-collisions-on-a-road/solutions/1352569/da-an-hui-bei-zhuang-ting-de-che-liang-s-yyfl/
        vector<char> stack;
        for (auto direction : directions) {
            if (direction == 'L') {
                if (stack.empty() == true) {
                    continue;
                }
                while ((stack.empty() == false) && (stack.back() == 'R')) {
                    retVal += 1;
                    stack.pop_back();
                }
                retVal += 1;
                stack.emplace_back('S');
            } else if (direction == 'R') {
                stack.emplace_back(direction);
            } else if (direction == 'S') {
                while ((stack.empty() == false) && (stack.back() == 'R')) {
                    retVal += 1;
                    stack.pop_back();
                }
                stack.emplace_back(direction);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string directions;
    };
    vector<subject> testData{{"RLRSLL"}, {"LLRR"}, {"SSRSSRLLRSLLRSRSSRLRRRRLLRRLSSRR"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: directions = "RLRSLL"
     *  Output: 5
     *
     *  Input: directions = "LLRR"
     *  Output: 0
     *
     *  Input: directions = "SSRSSRLLRSLLRSRSSRLRRRRLLRRLSSRR"
     *  Output: 20
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: directions = \"" << testData[i].directions << "\"\n";

        answer = cSolution.countCollisions(testData[i].directions);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
