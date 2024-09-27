#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class MyCalendarTwo {
   private:
    // Return true if the booking [start1, end1) & [start2, end2) overlaps.
    bool doesOverlap(int start1, int end1, int start2, int end2) {
        bool retVal = false;

        if (max(start1, start2) < min(end1, end2)) {
            retVal = true;
        }

        return retVal;
    }
    // Return overlapping booking between [start1, end1) & [start2, end2).
    pair<int, int> getOverlapped(int start1, int end1, int start2, int end2) {
        pair<int, int> retVal;

        retVal = {max(start1, start2), min(end1, end2)};

        return retVal;
    }

   public:
    vector<pair<int, int>> bookings;
    vector<pair<int, int>> overlapBookings;

    MyCalendarTwo() {}
    bool book(int start, int end) {
        bool retVal = false;

        // Returns false if the new booking overlaps with the existing double-booked bookings.
        for (pair<int, int> booking : overlapBookings) {
            if (doesOverlap(booking.first, booking.second, start, end) == true) {
                return retVal;
            }
        }

        // Add the double overlapping if any with the new booking.
        for (pair<int, int> booking : bookings) {
            if (doesOverlap(booking.first, booking.second, start, end) == true) {
                overlapBookings.push_back(getOverlapped(booking.first, booking.second, start, end));
            }
        }

        // Add the booking to the list of bookings.
        bookings.push_back({start, end});
        retVal = true;

        return retVal;
    }
};
/**
 * Your MyCalendarTwo object will be instantiated and called as such:
 * MyCalendarTwo* obj = new MyCalendarTwo();
 * bool param_1 = obj->book(start,end);
 */

int main(int argc, char **argv) {
    struct subject {
        vector<string> methods;
        vector<vector<int>> values;
    };
    vector<subject> testData{{{"MyCalendarTwo", "book", "book", "book", "book", "book", "book"},
                              {{}, {10, 20}, {50, 60}, {10, 40}, {5, 15}, {5, 10}, {25, 55}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input
     *  ["MyCalendarTwo", "book", "book", "book", "book", "book", "book"]
     *  [[], [10, 20], [50, 60], [10, 40], [5, 15], [5, 10], [25, 55]]
     *  Output
     *  [null, true, true, true, false, true, true]
     */

    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            cout << (j == 0 ? "" : ",") << '"' << testData[i].methods[j] << '"';
        }
        cout << "]\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].values.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].values[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].values[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        MyCalendarTwo cMyCalendar;
        cout << "Output\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            cout << (j == 0 ? "" : ",");
            if (testData[i].methods[j].compare("MyCalendarTwo") == 0) {
                cout << "null";
            } else if (testData[i].methods[j].compare("book") == 0) {
                bool retVal = cMyCalendar.book(testData[i].values[j][0], testData[i].values[j][1]);
                cout << (retVal == true ? "true" : "false");
            }
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
