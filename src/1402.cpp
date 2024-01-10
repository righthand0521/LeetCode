#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxSatisfaction(vector<int>& satisfaction) {
        int retVal = 0;

        sort(satisfaction.begin(), satisfaction.end(), [&](const int& x, const int& y) {
            // descending order
            return (x > y);
        });

        int sum = 0;
        for (auto iterator : satisfaction) {
            sum += iterator;
            if (sum <= 0) {
                break;
            }
            retVal += sum;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> satisfaction;
    };
    vector<subject> testData{{{-1, -8, 0, 5, -9}}, {{4, 3, 2}}, {{-1, -4, -5}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: satisfaction = [-1,-8,0,5,-9]
     *  Output: 14
     *
     *  Input: satisfaction = [4,3,2]
     *  Output: 20
     *
     *  Input: satisfaction = [-1,-4,-5]
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: satisfaction = [";
        for (long unsigned int j = 0; j < testData[i].satisfaction.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].satisfaction[j];
        }
        cout << "]\n";

        answer = cSolution.maxSatisfaction(testData[i].satisfaction);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
