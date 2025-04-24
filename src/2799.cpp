#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   public:
    int countCompleteSubarrays(vector<int>& nums) {
        int retVal = 0;

        unordered_set<int> distinct(nums.begin(), nums.end());
        int distinctSize = distinct.size();

        unordered_map<int, int> hashTable;
        int numsSize = nums.size();
        int right = 0;
        for (int left = 0; left < numsSize; left++) {
            if (left > 0) {
                int remove = nums[left - 1];
                hashTable[remove]--;
                if (hashTable[remove] == 0) {
                    hashTable.erase(remove);
                }
            }

            int hashTableSize = hashTable.size();
            while (right < numsSize) {
                if (hashTableSize >= distinctSize) {
                    break;
                }

                int add = nums[right];
                hashTable[add]++;
                hashTableSize = hashTable.size();
                right++;
            }

            if (hashTableSize == distinctSize) {
                retVal += (numsSize - right + 1);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 3, 1, 2, 2}}, {{5, 5, 5, 5}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,3,1,2,2]
     *  Output: 4
     *
     *  Input: nums = [5,5,5,5]
     *  Output: 10
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.countCompleteSubarrays(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
