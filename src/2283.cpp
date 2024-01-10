#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    bool digitCount(string num) {
        bool retVal = false;

        int len = num.length();

#if (1)
        unordered_map<int, int> hashTable;

        for (int i = 0; i < len; ++i) {
            ++hashTable[num[i] - '0'];
        }

        for (int i = 0; i < len; i++) {
            if (hashTable[i] != num[i] - '0') {
                return retVal;
            }
        }
        retVal = true;
#else
#define MAX_HASH_TABLE (10 + 1)
        vector<char> hashTable(MAX_HASH_TABLE, '0');

        for (int i = 0; i < len; ++i) {
            ++hashTable[num[i] - '0'];
        }

        string hashTableString(hashTable.begin(), hashTable.end());
        if ((hashTableString.compare(0, len, num)) == 0) {
            retVal = true;
        }
#endif

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string num;
    };
    vector<subject> testData{{"1210"}, {"030"}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: num = \"" << testData[i].num << "\"\n";

        answer = cSolution.digitCount(testData[i].num);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
