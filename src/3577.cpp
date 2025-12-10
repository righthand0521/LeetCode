#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int countPermutations(vector<int>& complexity) {
        int retVal = 0;

        int complexitySize = complexity.size();
        if (*min_element(complexity.begin() + 1, complexity.end()) <= complexity[0]) {
            return retVal;
        }

        int mod = 1000000007;
        long long answer = 1;
        for (int i = 2; i < complexitySize; ++i) {
            answer = (answer * i) % mod;
        }
        retVal = answer;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> complexity;
    };
    vector<subject> testData{{{1, 2, 3}}, {{3, 3, 3, 4, 4, 4}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: complexity = [1,2,3]
     *  Output: 2
     *
     *  Input: complexity = [3,3,3,4,4,4]
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: complexity = [";
        for (long unsigned int j = 0; j < testData[i].complexity.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].complexity[j];
        }
        cout << "]\n";

        answer = cSolution.countPermutations(testData[i].complexity);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
