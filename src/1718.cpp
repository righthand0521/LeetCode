#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    bool findLexicographicallyLargestSequence(int index, vector<int>& result, vector<bool>& isNumberUsed, int target) {
        bool retVal = true;

        // If we have filled all positions, return true indicating success
        int resultSequenceSize = result.size();
        if (index == resultSequenceSize) {
            return retVal;
        }

        // If the current position is already filled, move to the next index
        if (result[index] != 0) {
            retVal = findLexicographicallyLargestSequence(index + 1, result, isNumberUsed, target);
            return retVal;
        }

        // Attempt to place numbers from target to 1 for a lexicographically largest result
        for (int numberToPlace = target; numberToPlace >= 1; numberToPlace--) {
            if (isNumberUsed[numberToPlace] == true) {
                continue;
            }
            isNumberUsed[numberToPlace] = true;
            result[index] = numberToPlace;

            // If placing number 1, move to the next index directly
            if (numberToPlace == 1) {
                if (findLexicographicallyLargestSequence(index + 1, result, isNumberUsed, target) == true) {
                    return retVal;
                }
            }
            // Place larger numbers at two positions if valid
            else if ((index + numberToPlace < resultSequenceSize) && (result[index + numberToPlace] == 0)) {
                result[index + numberToPlace] = numberToPlace;
                if (findLexicographicallyLargestSequence(index + 1, result, isNumberUsed, target) == true) {
                    return retVal;
                }
                // Undo the placement for backtracking
                result[index + numberToPlace] = 0;
            }

            // Undo current placement and mark the number as unused
            result[index] = 0;
            isNumberUsed[numberToPlace] = false;
        }
        retVal = false;

        return retVal;
    }

   public:
    vector<int> constructDistancedSequence(int n) {
        vector<int> retVal(2 * n - 1, 0);

        // Keep track of which numbers are already placed in the sequence
        vector<bool> isNumberUsed(n + 1, false);
        // Start recursive backtracking to construct the sequence
        findLexicographicallyLargestSequence(0, retVal, isNumberUsed, n);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{3}, {5}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 3
     *  Output: [3,1,2,3,2]
     *
     *  Input: n = 5
     *  Output: [5,3,1,4,3,5,2,4,2]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.constructDistancedSequence(testData[i].n);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
