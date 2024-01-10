#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class SummaryRanges {
   private:
    map<int, int> intervals;

   public:
    SummaryRanges() {}
    void addNum(int value) {
        int left = value;
        int right = value;

        auto small_entry = intervals.upper_bound(value);
        if (small_entry != intervals.begin()) {
            auto max_entry = small_entry;
            --max_entry;
            if (max_entry->second >= value) {
                return;
            }

            if (max_entry->second == value - 1) {
                left = max_entry->first;
            }
        }
        if ((small_entry != intervals.end()) && (small_entry->first == value + 1)) {
            right = small_entry->second;
            intervals.erase(small_entry);
        }

        intervals[left] = right;
    }
    vector<vector<int>> getIntervals() {
        vector<vector<int>> retVal;

        for (const auto& p : intervals) {
            retVal.push_back({p.first, p.second});
        }

        return retVal;
    }
};
/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges* obj = new SummaryRanges();
 * obj->addNum(value);
 * vector<vector<int>> param_2 = obj->getIntervals();
 */

int main(int argc, char** argv) {
#define DISPLAY_NULL (-1)
    struct subject {
        vector<string> methods;
        vector<int> value;
    };
    vector<subject> testData{
        {{"SummaryRanges", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals", "addNum",
          "getIntervals", "addNum", "getIntervals"},
         {DISPLAY_NULL, 1, DISPLAY_NULL, 3, DISPLAY_NULL, 7, DISPLAY_NULL, 2, DISPLAY_NULL, 6, DISPLAY_NULL}}};
    int numberOfTestCase = testData.size();

    SummaryRanges cSolution;
    vector<vector<int>> retVal;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input\n[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            cout << ((j == 0) ? "" : ", ") << "\"" << testData[i].methods[j] << "\"";
        }
        cout << "]\n[";
        for (long unsigned int j = 0; j < testData[i].value.size(); ++j) {
            cout << ((j == 0) ? "" : ", ") << "[";
            if (testData[i].value[j] == DISPLAY_NULL) {
                cout << "";
            } else {
                cout << testData[i].value[j];
            }
            cout << "]";
        }
        cout << "]\n";

        cout << "Output\n[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            if (testData[i].methods[j].compare("SummaryRanges") == 0) {
                // cSolution.SummaryRanges();
                cout << ((j == 0) ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("addNum") == 0) {
                cSolution.addNum(testData[i].value[j]);
                cout << ((j == 0) ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("getIntervals") == 0) {
                retVal = cSolution.getIntervals();
                cout << ((j == 0) ? "" : ", ") << "[";
                for (long unsigned int row = 0; row < retVal.size(); ++row) {
                    cout << (row == 0 ? "" : ", ") << "[";
                    for (long unsigned int col = 0; col < retVal[row].size(); ++col) {
                        cout << (col == 0 ? "" : ", ") << retVal[row][col];
                    }
                    cout << "]";
                }
                cout << "]";
            }
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
