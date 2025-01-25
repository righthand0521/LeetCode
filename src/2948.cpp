#include <algorithm>
#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        vector<int> retVal = nums;

        int returnSize = retVal.size();

        vector<int> numsSorted(retVal);
        sort(numsSorted.begin(), numsSorted.end());

        int currGroup = 0;
        unordered_map<int, int> numToGroup;
        numToGroup.insert(pair<int, int>(numsSorted[0], currGroup));

        unordered_map<int, list<int>> groupToList;
        groupToList.insert(pair<int, list<int>>(currGroup, list<int>(1, numsSorted[0])));

        for (int i = 1; i < returnSize; i++) {
            if (abs(numsSorted[i] - numsSorted[i - 1]) > limit) {
                currGroup++;
            }
            numToGroup.insert(pair<int, int>(numsSorted[i], currGroup));

            if (groupToList.find(currGroup) == groupToList.end()) {
                groupToList[currGroup] = list<int>();
            }
            groupToList[currGroup].push_back(numsSorted[i]);
        }

        for (int i = 0; i < returnSize; i++) {
            int num = retVal[i];
            int group = numToGroup[num];
            retVal[i] = *groupToList[group].begin();
            groupToList[group].pop_front();
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int limit;
    };
    vector<subject> testData{{{1, 5, 3, 9, 8}, 2}, {{1, 7, 6, 18, 2, 1}, 3}, {{1, 7, 28, 19, 10}, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,5,3,9,8], limit = 2
     *  Output: [1,3,5,8,9]
     *
     *  Input: nums = [1,7,6,18,2,1], limit = 3
     *  Output: [1,6,7,18,1,2]
     *
     *  Input: nums = [1,7,28,19,10], limit = 3
     *  Output: [1,7,28,19,10]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], limit = " << testData[i].limit << "\n";

        answer = cSolution.lexicographicallySmallestArray(testData[i].nums, testData[i].limit);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
