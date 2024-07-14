#include <algorithm>
#include <iostream>
#include <map>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    string countOfAtoms(string formula) {
        string retVal = "";

        int formulaSize = formula.size();

        stack<unordered_map<string, int>> stack;
        stack.push(unordered_map<string, int>());

        int index = 0;
        while (index < formulaSize) {
            if (formula[index] == '(') {
                // If left parenthesis, insert a new hashmap to the stack.
                // It will keep track of the atoms and their counts in the nested formula
                stack.push(unordered_map<string, int>());
                index++;
            } else if (formula[index] == ')') {
                // If right parenthesis, pop the top element from the stack.
                // Multiply the count with the multiplicity of the nested formula
                unordered_map<string, int> currMap = stack.top();
                stack.pop();

                index++;
                string multiplier;
                while ((index < formulaSize) && (isdigit(formula[index]))) {
                    multiplier += formula[index];
                    index++;
                }
                if (multiplier.empty() == false) {
                    int mult = stoi(multiplier);
                    for (auto& [atom, count] : currMap) {
                        currMap[atom] = count * mult;
                    }
                }

                for (auto& [atom, count] : currMap) {
                    stack.top()[atom] += count;
                }
            } else {
                // Otherwise, it must be a UPPERCASE LETTER.
                // Extract the complete atom with frequency, and update the most recent hashmap
                string currAtom;
                currAtom += formula[index];
                index++;
                while ((index < formulaSize) && (islower(formula[index]))) {
                    currAtom += formula[index];
                    index++;
                }

                string currCount;
                while ((index < formulaSize) && (isdigit(formula[index]))) {
                    currCount += formula[index];
                    index++;
                }

                int count = currCount.empty() ? 1 : stoi(currCount);
                stack.top()[currAtom] += count;
            }
        }

        map<string, int> finalMap(stack.top().begin(), stack.top().end());
        string ans;
        for (auto& [atom, count] : finalMap) {
            retVal += atom;
            if (count > 1) {
                retVal += to_string(count);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string formula;
    };
    vector<subject> testData{{"H2O"}, {"Mg(OH)2"}, {"K4(ON(SO3)2)2"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: formula = "H2O"
     *  Output: "H2O"
     *
     *  Input: formula = "Mg(OH)2"
     *  Output: "H2MgO2"
     *
     *  Input: formula = "K4(ON(SO3)2)2"
     *  Output: "K4N2O14S4"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: formula = \"" << testData[i].formula << "\"\n";

        answer = cSolution.countOfAtoms(testData[i].formula);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
