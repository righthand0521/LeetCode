#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Solution {
   public:
    int mostFrequentEven(vector<int>& nums) {
        int retVal = -1;

        //
        map<int, int> hashTable;
        for (int num : nums) {
            if (num % 2 != 0) {
                continue;
            }
            ++hashTable[num];
        }
        if (hashTable.size() == 0) {
            return retVal;
        }

        //
        vector<pair<int, int>> sortHashTable;
        for (auto iterator = hashTable.begin(); iterator != hashTable.end(); ++iterator) {
            sortHashTable.push_back(*iterator);
        }
        sort(sortHashTable.begin(), sortHashTable.end(), [=](pair<int, int>& a, pair<int, int>& b) {
            return a.second == b.second ? a.first < b.first : a.second > b.second;
        });
        retVal = sortHashTable[0].first;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{0, 1, 2, 2, 4, 4, 1}}, {{4, 4, 4, 9, 2, 4}}, {{29, 47, 21, 41, 13, 37, 25, 7}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [0,1,2,2,4,4,1]
     *  Output: 2
     *
     *  Input: nums = [4,4,4,9,2,4]
     *  Output: 4
     *
     *  Input: nums = [29,47,21,41,13,37,25,7]
     *  Output: -1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.mostFrequentEven(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
