#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int numRescueBoats(vector<int>& people, int limit) {
        int retVal = 0;

        sort(people.begin(), people.end());

        int left = 0;
        int right = people.size() - 1;
        while (left <= right) {
            if (people[left] + people[right] <= limit) {
                ++left;
            }
            --right;
            ++retVal;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> people;
        int limit;
    };
    vector<subject> testData{{{1, 2}, 3}, {{3, 2, 2, 1}, 3}, {{3, 5, 3, 4}, 5}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: people = [1,2], limit = 3
     *  Output: 1
     *
     *  Input: people = [3,2,2,1], limit = 3
     *  Output: 3
     *
     *  Input: people = [3,5,3,4], limit = 5
     *  Output: 4
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: people = [";
        for (long unsigned int j = 0; j < testData[i].people.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].people[j];
        }
        cout << "], limit = " << testData[i].limit << "\n";

        answer = cSolution.numRescueBoats(testData[i].people, testData[i].limit);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
