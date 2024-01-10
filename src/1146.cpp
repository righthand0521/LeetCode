#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class SnapshotArray {
    int snapId;
    vector<vector<pair<int, int>>> historyRecords;

   public:
    SnapshotArray(int length) {
        snapId = 0;
        historyRecords.resize(length);
        for (int i = 0; i < length; ++i) {
            historyRecords[i].push_back(make_pair(0, 0));
        }
    }
    void set(int index, int val) {
        //
        historyRecords[index].push_back(make_pair(snapId, val));
    }
    int snap() {
        int retVal = snapId;

        ++snapId;

        return retVal;
    }
    int get(int index, int snap_id) {
        int retVal = 0;

        auto it = upper_bound(historyRecords[index].begin(), historyRecords[index].end(),
                              make_pair(snap_id, numeric_limits<int>::max()));
        retVal = prev(it)->second;

        return retVal;
    }
};
/**
 * Your SnapshotArray object will be instantiated and called as such:
 * SnapshotArray* obj = new SnapshotArray(length);
 * obj->set(index,val);
 * int param_2 = obj->snap();
 * int param_3 = obj->get(index,snap_id);
 */

int main(int argc, char **argv) {
    struct subject {
        vector<string> methods;
        vector<vector<int>> values;
    };
    vector<subject> testData{{{"SnapshotArray", "set", "snap", "set", "get"}, {{3}, {0, 5}, {}, {0, 6}, {0, 0}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: ["SnapshotArray","set","snap","set","get"]
     *  [[3],[0,5],[],[0,6],[0,0]]
     *  Output: [null,null,0,null,5]
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

        SnapshotArray cSnapshotArray(testData[i].values[0][0]);
        cout << "Output\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            cout << (j == 0 ? "" : ",");
            if (testData[i].methods[j].compare("SnapshotArray") == 0) {
                cout << "null";
            } else if (testData[i].methods[j].compare("set") == 0) {
                cSnapshotArray.set(testData[i].values[j][0], testData[i].values[j][1]);
                cout << "null";
            } else if (testData[i].methods[j].compare("snap") == 0) {
                int retVal = cSnapshotArray.snap();
                cout << retVal;
            } else if (testData[i].methods[j].compare("get") == 0) {
                int retVal = cSnapshotArray.get(testData[i].values[j][0], testData[i].values[j][1]);
                cout << retVal;
            }
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
