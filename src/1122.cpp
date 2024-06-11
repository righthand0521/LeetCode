#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        vector<int> retVal;

        int upper = *max_element(arr1.begin(), arr1.end());
        vector<int> frequency(upper + 1, 0);
        for (int x : arr1) {
            frequency[x] += 1;
        }

        for (int x : arr2) {
            for (int i = 0; i < frequency[x]; ++i) {
                retVal.emplace_back(x);
            }
            frequency[x] = 0;
        }
        for (int x = 0; x < upper + 1; ++x) {
            if (frequency[x] != 0) {
                for (int i = 0; i < frequency[x]; ++i) {
                    retVal.emplace_back(x);
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> arr1;
        vector<int> arr2;
    };
    vector<subject> testData{{{2, 3, 1, 3, 2, 4, 6, 7, 9, 2, 19}, {2, 1, 4, 3, 9, 6}},
                             {{28, 6, 22, 8, 44, 17}, {22, 28, 8, 6}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: arr1 = [2,3,1,3,2,4,6,7,9,2,19], arr2 = [2,1,4,3,9,6]
     *  Output: [2,2,2,1,4,3,3,9,6,7,19]
     *
     *  Input: arr1 = [28,6,22,8,44,17], arr2 = [22,28,8,6]
     *  Output: [22,28,8,6,17,44]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: arr1 = [";
        for (long unsigned int j = 0; j < testData[i].arr1.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].arr1[j];
        }
        cout << "], arr2 = [";
        for (long unsigned int j = 0; j < testData[i].arr2.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].arr2[j];
        }
        cout << "]\n";

        answer = cSolution.relativeSortArray(testData[i].arr1, testData[i].arr2);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
