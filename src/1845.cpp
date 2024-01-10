#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class SeatManager {
   private:
    priority_queue<int, vector<int>, greater<int>> seats;

   public:
    SeatManager(int n) {
        for (int seatNumber = 1; seatNumber <= n; ++seatNumber) {
            seats.push(seatNumber);
        }
    }
    int reserve() {
        int retVal = 0;

        retVal = seats.top();
        seats.pop();

        return retVal;
    }
    void unreserve(int seatNumber) {
        //
        seats.push(seatNumber);
    }
};
/**
 * Your SeatManager object will be instantiated and called as such:
 * SeatManager* obj = new SeatManager(n);
 * int param_1 = obj->reserve();
 * obj->unreserve(seatNumber);
 */

int main(int argc, char **argv) {
    struct subject {
        vector<string> methods;
        vector<vector<int>> seat;
    };
    vector<subject> testData{
        {{"SeatManager", "reserve", "reserve", "unreserve", "reserve", "reserve", "reserve", "reserve", "unreserve"},
         {{5}, {}, {}, {2}, {}, {}, {}, {}, {5}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input
     *  ["SeatManager", "reserve", "reserve", "unreserve", "reserve", "reserve", "reserve", "reserve", "unreserve"]
     *  [[5], [], [], [2], [], [], [], [], [5]]
     *  Output
     *  [null, 1, 2, null, 2, 3, 4, 5, null]
     */

    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            cout << (j == 0 ? "" : ", ") << '"' << testData[i].methods[j] << '"';
        }
        cout << "]\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].seat.size(); ++j) {
            cout << (j == 0 ? "" : ", ") << "[";
            for (long unsigned int k = 0; k < testData[i].seat[j].size(); ++k) {
                cout << (k == 0 ? "" : ", ") << testData[i].seat[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        SeatManager cParkingSystem(testData[i].seat[0][0]);
        cout << "Output\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            if (testData[i].methods[j].compare("SeatManager") == 0) {
                cout << (j == 0 ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("reserve") == 0) {
                int retVal = cParkingSystem.reserve();
                cout << (j == 0 ? "" : ", ") << retVal;
            } else if (testData[i].methods[j].compare("unreserve") == 0) {
                cParkingSystem.unreserve(testData[i].seat[j][0]);
                cout << (j == 0 ? "" : ", ") << "null";
            }
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
