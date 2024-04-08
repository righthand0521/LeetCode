#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int countStudents(vector<int>& students, vector<int>& sandwiches) {
        int retVal = 0;

        // The school cafeteria offers circular and square sandwiches at lunch break,
        // referred to by numbers 0 and 1 respectively.
        int circular = 0;
        int square = 0;
        for (int student : students) {
            if (student == 0) {
                circular++;
            } else if (student == 1) {
                square++;
            }
        }

        for (int sandwiche : sandwiches) {
            if ((sandwiche == 0) && (circular != 0)) {
                circular--;
            } else if ((sandwiche == 1) && (square != 0)) {
                square--;
            } else {
                retVal = circular + square;
                break;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> students;
        vector<int> sandwiches;
    };
    vector<subject> testData{{{1, 1, 0, 0}, {0, 1, 0, 1}}, {{1, 1, 1, 0, 0, 1}, {1, 0, 0, 0, 1, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: students = [1,1,0,0], sandwiches = [0,1,0,1]
     *  Output: 0
     *
     *  Input: students = [1,1,1,0,0,1], sandwiches = [1,0,0,0,1,1]
     *  Output: 3
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: students = [";
        for (long unsigned int j = 0; j < testData[i].students.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].students[j];
        }
        cout << "], sandwiches = [";
        for (long unsigned int j = 0; j < testData[i].sandwiches.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].sandwiches[j];
        }
        cout << "]\n";

        answer = cSolution.countStudents(testData[i].students, testData[i].sandwiches);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
