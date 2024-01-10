#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int latestTimeCatchTheBus(vector<int>& buses, vector<int>& passengers, int capacity) {
        int retVal = 0;

        //
        int busesSize = buses.size();
        int busesIdx = 0;
        sort(buses.begin(), buses.end());
        int passengersSize = passengers.size();
        int passengersIdx = 0;
        sort(passengers.begin(), passengers.end());
        int capacityIdx;

        //
        capacityIdx = 0;
        while ((busesIdx < (busesSize - 1)) && (passengersIdx < passengersSize)) {
            if ((passengers[passengersIdx] <= buses[busesIdx]) && (capacityIdx < capacity)) {
                ++passengersIdx;
                ++capacityIdx;
            } else {
                ++busesIdx;
                capacityIdx = 0;
            }
        }
        capacityIdx = 0;
        while ((passengersIdx < passengersSize) && (passengers[passengersIdx] <= buses[busesSize - 1]) &&
               (capacityIdx < capacity)) {
            ++passengersIdx;
            ++capacityIdx;
        }

        //
        if (capacityIdx < capacity) {
            retVal = buses[busesSize - 1];
        } else {
            retVal = passengers[passengersIdx - 1];
        }
        --passengersIdx;
        while ((passengersIdx >= 0) && (retVal == passengers[passengersIdx])) {
            retVal = passengers[passengersIdx] - 1;
            --passengersIdx;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> buses;
        vector<int> passengers;
        int capacity;
    };
    vector<subject> testData{{{10, 20}, {2, 17, 18, 19}, 2}, {{20, 30, 10}, {19, 13, 26, 4, 25, 11, 21}, 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: buses = [10,20], passengers = [2,17,18,19], capacity = 2
     *  Output: 16
     *
     *  Input: buses = [20,30,10], passengers = [19,13,26,4,25,11,21], capacity = 2
     *  Output: 20
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: buses = [";
        for (long unsigned int j = 0; j < testData[i].buses.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].buses[j];
        }
        cout << "], passengers = [";
        for (long unsigned int j = 0; j < testData[i].passengers.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].passengers[j];
        }
        cout << "], capacity = " << testData[i].capacity << "\n";

        answer = cSolution.latestTimeCatchTheBus(testData[i].buses, testData[i].passengers, testData[i].capacity);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
