#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minMovesToSeat(vector<int>& seats, vector<int>& students) {
        int retVal = 0;

        sort(seats.begin(), seats.end());
        sort(students.begin(), students.end());

        int seatsSize = seats.size();
        for (int i = 0; i < seatsSize; ++i) {
            retVal += abs(seats[i] - students[i]);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> seats;
        vector<int> students;
    };
    vector<subject> testData{{{3, 1, 5}, {2, 7, 4}}, {{4, 1, 5, 9}, {1, 3, 2, 6}}, {{2, 2, 6, 6}, {1, 3, 2, 6}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: seats = [3,1,5], students = [2,7,4]
     *  Output: 4
     *
     *  Input: seats = [4,1,5,9], students = [1,3,2,6]
     *  Output: 7
     *
     *  Input: seats = [2,2,6,6], students = [1,3,2,6]
     *  Output: 4
     */

    Solution cSolution;
    double answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: seats = [";
        for (long unsigned int j = 0; j < testData[i].seats.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].seats[j];
        }
        cout << "], students = [";
        for (long unsigned int j = 0; j < testData[i].students.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].students[j];
        }
        cout << "]\n";

        answer = cSolution.minMovesToSeat(testData[i].seats, testData[i].students);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
