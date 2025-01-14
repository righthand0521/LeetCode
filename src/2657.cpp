#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B) {
        vector<int> retVal;

        int ASize = A.size();
        retVal.resize(ASize, 0);

        vector<int> frequency(ASize + 1, 0);
        int commonCount = 0;
        for (int currentIndex = 0; currentIndex < ASize; ++currentIndex) {
            frequency[A[currentIndex]]++;
            if (frequency[A[currentIndex]] == 2) {
                ++commonCount;
            }

            frequency[B[currentIndex]]++;
            if (frequency[B[currentIndex]] == 2) {
                ++commonCount;
            }

            retVal[currentIndex] = commonCount;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> A;
        vector<int> B;
    };
    vector<subject> testData{{{1, 3, 2, 4}, {3, 1, 2, 4}}, {{2, 3, 1}, {3, 1, 2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: A = [1,3,2,4], B = [3,1,2,4]
     *  Output: [0,2,3,4]
     *
     *  Input: A = [2,3,1], B = [3,1,2]
     *  Output: [0,1,3]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: A = [";
        for (long unsigned int j = 0; j < testData[i].A.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].A[j];
        }
        cout << "], B = [";
        for (long unsigned int j = 0; j < testData[i].B.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].B[j];
        }
        cout << "]\n";

        answer = cSolution.findThePrefixCommonArray(testData[i].A, testData[i].B);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
