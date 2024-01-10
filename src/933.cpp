#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class RecentCounter {
    queue<int> requests;

   public:
    RecentCounter() {
        //
    }
    int ping(int t) {
        int retVal = 0;

        requests.emplace(t);
        while (requests.empty() == false) {
            int value = requests.front();
            if (value >= t - 3000) {
                break;
            }
            requests.pop();
        }
        retVal = requests.size();

        return retVal;
    }
};
/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */

int main(int argc, char** argv) {
    struct subject {
        // unordered_map<string, int> calls;
        vector<string> methods;
        vector<int> num;
    };
    vector<subject> testData{{{"RecentCounter", "ping", "ping", "ping", "ping"}, {0, 1, 100, 3001, 3002}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input
     *  ["RecentCounter", "ping", "ping", "ping", "ping"]
     *  [[], [1], [100], [3001], [3002]]
     *  Output
     *  [null, 1, 2, 3, 3]
     */

    for (int i = 0; i < numberOfTestCase; ++i) {
        RecentCounter cRecentCounter;

        cout << "Input\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            cout << (j == 0 ? "" : ", ") << '"' << testData[i].methods[j] << '"';
        }
        cout << "]\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].num.size(); ++j) {
            cout << (j == 0 ? "" : ", ") << "[";
            if (j == 0) {
                if (i == 0) {
                    cout << "";
                }
            } else {
                cout << testData[i].num[j];
            }
            cout << "]";
        }
        cout << "]\n";

        cout << "Output\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            if (testData[i].methods[j].compare("RecentCounter") == 0) {
                cout << (j == 0 ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("ping") == 0) {
                int retVal = cRecentCounter.ping(testData[i].num[j]);
                cout << (j == 0 ? "" : ", ") << retVal;
            }
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
