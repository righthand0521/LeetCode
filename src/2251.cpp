#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> fullBloomFlowers(vector<vector<int>>& flowers, vector<int>& people) {
        vector<int> retVal;

        vector<int> starts;
        vector<int> ends;
        for (vector<int>& flower : flowers) {
            starts.push_back(flower[0]);
            ends.push_back(flower[1] + 1);
        }
        sort(starts.begin(), starts.end());
        sort(ends.begin(), ends.end());

        for (int p : people) {
            int i = upper_bound(starts.begin(), starts.end(), p) - starts.begin();
            int j = upper_bound(ends.begin(), ends.end(), p) - ends.begin();
            retVal.push_back(i - j);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> flowers;
        vector<int> people;
    };
    vector<subject> testData{{{{1, 6}, {3, 7}, {9, 12}, {4, 13}}, {2, 3, 7, 11}}, {{{1, 10}, {3, 3}}, {3, 3, 2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: flowers = [[1,6],[3,7],[9,12],[4,13]], poeple = [2,3,7,11]
     *  Output: [1,2,2,2]
     *
     *  Input: flowers = [[1,10],[3,3]], poeple = [3,3,2]
     *  Output: [2,2,1]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: flowers = [";
        for (long unsigned int j = 0; j < testData[i].flowers.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].flowers[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].flowers[j][k];
            }
            cout << "]";
        }
        cout << "], poeple = [";
        for (long unsigned int j = 0; j < testData[i].people.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].people[j];
        }
        cout << "]\n";

        answer = cSolution.fullBloomFlowers(testData[i].flowers, testData[i].people);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
