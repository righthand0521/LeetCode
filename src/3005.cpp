#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    int numsMAXsize = 100;  // 1 <= nums.length <= 100; 1 <= nums[i] <= 100;

   public:
    int maxFrequencyElements(vector<int>& nums) {
        int retVal = 0;

        vector<int> hashTable(numsMAXsize, 0);
        for (int num : nums) {
            hashTable[num - 1]++;
        }
        sort(hashTable.begin(), hashTable.end(), greater());

        int maxFrequency = 0;
        for (int frequency : hashTable) {
            if (frequency >= maxFrequency) {
                maxFrequency = frequency;
                retVal += frequency;
            } else {
                break;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 2, 2, 3, 1, 4}}, {{1, 2, 3, 4, 5}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2,2,3,1,4]
     *  Output: 4
     *
     *  Input: nums = [1,2,3,4,5]
     *  Output: 5
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.maxFrequencyElements(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
