#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class StockSpanner {
   public:
    stack<pair<int, int>> monotonicStack;

    StockSpanner() {
        //
    }
    int next(int price) {
        int retVal = 1;

        while ((monotonicStack.empty() == false) && (monotonicStack.top().first <= price)) {
            retVal += monotonicStack.top().second;
            monotonicStack.pop();
        }
        monotonicStack.push({price, retVal});

        return retVal;
    }
};
/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */

int main(int argc, char **argv) {
    struct subject {
        string calls;
        int price;
    };
    vector<subject> testData{{"StockSpanner", 0}, {"next", 100}, {"next", 80}, {"next", 60},
                             {"next", 70},        {"next", 60},  {"next", 75}, {"next", 85}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input
     *  ["StockSpanner", "next", "next", "next", "next", "next", "next", "next"]
     *  [[], [100], [80], [60], [70], [60], [75], [85]]
     *  Output
     *  [null, 1, 1, 1, 2, 1, 4, 6]
     */

    cout << "Input\n";
    cout << "[";
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << (i == 0 ? "" : ", ") << "\"" << testData[i].calls << "\"";
    }
    cout << "]\n";
    cout << "[[]";
    for (int i = 1; i < numberOfTestCase; ++i) {
        cout << (i == 0 ? "" : ", ") << testData[i].price;
    }
    cout << "]\n";

    StockSpanner stockSpanner = StockSpanner();
    cout << "Output\n";
    cout << "[null";
    for (int i = 1; i < numberOfTestCase; ++i) {
        cout << (i == 0 ? "" : ", ") << stockSpanner.next(testData[i].price);
    }
    cout << "]\n";

    return EXIT_SUCCESS;
}
