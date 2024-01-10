#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
        vector<bool> retVal;

        int maxCandy = *max_element(candies.begin(), candies.end());
        for (auto candy : candies) {
            if (candy + extraCandies >= maxCandy) {
                retVal.emplace_back(true);
            } else {
                retVal.emplace_back(false);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> candies;
        int extraCandies;
    };
    vector<subject> testData{{{2, 3, 5, 1, 3}, 3}, {{4, 2, 1, 1, 2}, 1}, {{12, 1, 12}, 10}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: candies = [2,3,5,1,3], extraCandies = 3
     *  Output: [true,true,true,false,true]
     *
     *  Input: candies = [4,2,1,1,2], extraCandies = 1
     *  Output: [true,false,false,false,false]
     *
     *  Input: candies = [12,1,12], extraCandies = 10
     *  Output: [true,false,true]
     */

    Solution cSolution;
    vector<bool> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: candies = [";
        for (long unsigned int j = 0; j < testData[i].candies.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].candies[j];
        }
        cout << "], extraCandies = " << testData[i].extraCandies << "\n";

        answer = cSolution.kidsWithCandies(testData[i].candies, testData[i].extraCandies);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << (answer[j] == true ? "true" : "false");
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
