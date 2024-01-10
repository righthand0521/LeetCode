#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class KthLargest {
   public:
    priority_queue<int, vector<int>, greater<int>> priorityQueue;
    int k;

    KthLargest(int k, vector<int>& nums) {
        this->k = k;
        for (auto& num : nums) {
            add(num);
        }
    }
    int add(int val) {
        int retVal = 0;

        priorityQueue.push(val);
        int priorityQueueSize = priorityQueue.size();
        if (priorityQueueSize > k) {
            priorityQueue.pop();
        }
        retVal = priorityQueue.top();

        return retVal;
    }
};
/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */

int main(int argc, char** argv) {
    struct subject {
        // unordered_map<string, int> calls;
        vector<string> methods;
        vector<int> num;
    };
    vector<subject> testData{{{"KthLargest", "add", "add", "add", "add", "add"}, {0, 3, 5, 10, 9, 4}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input
     *  ["KthLargest", "add", "add", "add", "add", "add"]
     *  [[3, [4, 5, 8, 2]], [3], [5], [10], [9], [4]]
     *  Output
     *  [null, 4, 5, 5, 8, 8]
     */

    for (int i = 0; i < numberOfTestCase; ++i) {
        vector<int> nums;
        if (i == 0) {
            nums.emplace_back(4);
            nums.emplace_back(5);
            nums.emplace_back(8);
            nums.emplace_back(2);
        }
        KthLargest cKthLargest(3, nums);

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
                    cout << "3, [4, 5, 8, 2]";
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
            if (testData[i].methods[j].compare("KthLargest") == 0) {
                cout << (j == 0 ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("add") == 0) {
                int retVal = cKthLargest.add(testData[i].num[j]);
                cout << (j == 0 ? "" : ", ") << retVal;
            }
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
