#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

class MyCalendar {
   private:
    set<pair<int, int>> calendar;

   public:
    MyCalendar() {}
    bool book(int start, int end) {
        bool retVal = false;

        const pair<int, int> event{start, end};
        const auto nextEvent = calendar.lower_bound(event);
        if ((nextEvent != calendar.end()) && (nextEvent->first < end)) {
            return retVal;
        }

        if (nextEvent != calendar.begin()) {
            const auto prevEvent = prev(nextEvent);
            if (prevEvent->second > start) {
                return retVal;
            }
        }
        calendar.insert(event);
        retVal = true;

        return retVal;
    }
};
/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */

int main(int argc, char **argv) {
    struct subject {
        vector<string> methods;
        vector<vector<int>> values;
    };
    vector<subject> testData{{{"MyCalendar", "book", "book", "book"}, {{}, {10, 20}, {15, 25}, {20, 30}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input
     *  ["MyCalendar", "book", "book", "book"]
     *  [[], [10, 20], [15, 25], [20, 30]]
     *  Output
     *  [null, true, false, true]
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

        MyCalendar cMyCalendar;
        cout << "Output\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            cout << (j == 0 ? "" : ",");
            if (testData[i].methods[j].compare("MyCalendar") == 0) {
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
