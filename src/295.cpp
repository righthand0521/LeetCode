#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class MedianFinder {
   public:
    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;

    MedianFinder() {}

    void addNum(int num) {
        maxHeap.push(num);
        minHeap.push(maxHeap.top());
        maxHeap.pop();
        if (minHeap.size() > maxHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }

    double findMedian() {
        if (maxHeap.size() > minHeap.size()) return maxHeap.top();
        return (maxHeap.top() + minHeap.top()) / 2.0;
    }
};
/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */

int main(int argc, char **argv) {
    struct subject {
        // unordered_map<string, int> calls;

        vector<string> methods;
        vector<int> num;
    };
    vector<subject> testData{
        {{"MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"},
         {INT_MIN, 1, 2, INT_MIN, 3, INT_MIN}},
        {{"MedianFinder", "addNum", "findMedian", "addNum", "findMedian", "addNum", "findMedian", "addNum",
          "findMedian",   "addNum", "findMedian", "addNum", "findMedian", "addNum", "findMedian", "addNum",
          "findMedian",   "addNum", "findMedian", "addNum", "findMedian", "addNum", "findMedian"},
         {INT_MIN, 6, INT_MIN, 10, INT_MIN, 2, INT_MIN, 6, INT_MIN, 5, INT_MIN, 0,
          INT_MIN, 6, INT_MIN, 3,  INT_MIN, 1, INT_MIN, 0, INT_MIN, 0, INT_MIN}

        }};
    int numberOfTestCase = testData.size();

    for (int i = 0; i < numberOfTestCase; ++i) {
        MedianFinder cMedianFinder;

        cout << "Input\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            cout << (j == 0 ? "" : ", ") << '"' << testData[i].methods[j] << '"';
        }
        cout << "]"
             << "\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].num.size(); ++j) {
            cout << (j == 0 ? "" : ", ") << "[";
            if (testData[i].num[j] != INT_MIN) {
                cout << testData[i].num[j];
            }
            cout << "]";
        }
        cout << "]"
             << "\n";

        cout << "Output\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            if (testData[i].methods[j].compare("MedianFinder") == 0) {
                cout << (j == 0 ? "" : ", ") << "null";
            }
            if (testData[i].methods[j].compare("addNum") == 0) {
                cMedianFinder.addNum(testData[i].num[j]);
                cout << (j == 0 ? "" : ", ") << "null";
            }
            if (testData[i].methods[j].compare("findMedian") == 0) {
                double retVal = cMedianFinder.findMedian();
                cout << (j == 0 ? "" : ", ") << retVal;
            }
        }
        cout << "]"
             << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
