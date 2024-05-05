#include <algorithm>
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

        int maxHeapSize = maxHeap.size();
        int minHeapSize = minHeap.size();
        if (minHeapSize > maxHeapSize) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }
    double findMedian() {
        double retVal = maxHeap.top();

        int maxHeapSize = maxHeap.size();
        int minHeapSize = minHeap.size();
        if (maxHeapSize > minHeapSize) {
            return retVal;
        }
        retVal = (maxHeap.top() + minHeap.top()) / 2.0;

        return retVal;
    }
};
/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */

int main(int argc, char** argv) {
    struct subject {
        vector<string> methods;
        vector<int> num;
    };
    vector<subject> testData{
        {{"MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"}, {0, 1, 2, 0, 3, 0}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input
     *  ["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
     *  [[], [1], [2], [], [3], []]
     *  Output
     *  [null, null, null, 1.5, null, 2.0]
     */

    for (int i = 0; i < numberOfTestCase; ++i) {
        MedianFinder cMedianFinder;

        cout << "Input\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            cout << (j == 0 ? "" : ", ") << '"' << testData[i].methods[j] << '"';
        }
        cout << "]\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].num.size(); ++j) {
            cout << (j == 0 ? "" : ", ") << "[";
            if (testData[i].num[j] != 0) {
                cout << testData[i].num[j];
            }
            cout << "]";
        }
        cout << "]\n";

        cout << "Output\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            if (testData[i].methods[j].compare("MedianFinder") == 0) {
                cout << (j == 0 ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("addNum") == 0) {
                cMedianFinder.addNum(testData[i].num[j]);
                cout << (j == 0 ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("findMedian") == 0) {
                double retVal = cMedianFinder.findMedian();
                cout.setf(ios::fixed);
                cout.precision(1);
                cout << (j == 0 ? "" : ", ") << retVal;
            }
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
