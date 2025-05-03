#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    int check(vector<int>& tops, vector<int>& bottoms, int x) {
        int retVal = -1;

        int rotationsTops = 0;
        int rotationsBottoms = 0;
        int topsSize = tops.size();
        for (int i = 0; i < topsSize; i++) {
            if (tops[i] != x && bottoms[i] != x) {  // rotations couldn't be done
                return retVal;
            }

            if (tops[i] != x) {  // tops[i] != x and bottoms[i] == x
                rotationsTops++;
            } else if (bottoms[i] != x) {  // tops[i] == x and bottoms[i] != x
                rotationsBottoms++;
            }
        }
        // min number of rotations to have all elements equal to x in tops or bottoms
        retVal = min(rotationsTops, rotationsBottoms);

        return retVal;
    }

   public:
    int minDominoRotations(vector<int>& tops, vector<int>& bottoms) {
        int retVal = 0;

        int rotations = check(tops, bottoms, tops[0]);
        // If one could make all elements in tops or bottoms equal to tops[0]
        // Else one could make all elements in tops or bottoms equal to bottoms[0]
        if ((rotations != -1) || (tops[0] == bottoms[0])) {
            return rotations;
        } else {
            retVal = check(tops, bottoms, bottoms[0]);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> tops;
        vector<int> bottoms;
    };
    vector<subject> testData{{{2, 1, 2, 4, 2, 2}, {5, 2, 6, 2, 3, 2}}, {{3, 5, 1, 2, 3}, {3, 6, 3, 3, 4}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: tops = [2,1,2,4,2,2], bottoms = [5,2,6,2,3,2]
     *  Output: 2
     *
     *  Input: tops = [3,5,1,2,3], bottoms = [3,6,3,3,4]
     *  Output: -1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: tops = [";
        for (long unsigned int j = 0; j < testData[i].tops.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].tops[j];
        }
        cout << "], bottoms = [";
        for (long unsigned int j = 0; j < testData[i].bottoms.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].bottoms[j];
        }
        cout << "]\n";

        answer = cSolution.minDominoRotations(testData[i].tops, testData[i].bottoms);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
