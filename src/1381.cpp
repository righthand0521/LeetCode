#include <algorithm>
#include <iostream>
#include <list>
#include <stack>
#include <vector>

using namespace std;

class CustomStack {
   private:
    list<int> stack;
    int maxSize;

   public:
    CustomStack(int maxSize) {
        //
        this->maxSize = maxSize;
    }
    void push(int x) {
        int stackSize = stack.size();
        if (stackSize < maxSize) {
            stack.push_back(x);
        }
    }
    int pop() {
        int retVal = -1;  // Pops and returns the top of the stack or -1 if the stack is empty.

        if (stack.empty()) {
            return retVal;
        }
        retVal = stack.back();
        stack.pop_back();

        return retVal;
    }
    void increment(int k, int val) {
        auto iterator = stack.begin();
        for (int i = 0; (i < k && iterator != stack.end()); (i++, iterator++)) {
            (*iterator) += val;
        }
    }
};
/**
 * Your CustomStack object will be instantiated and called as such:
 * CustomStack* obj = new CustomStack(maxSize);
 * obj->push(x);
 * int param_2 = obj->pop();
 * obj->increment(k,val);
 */

int main(int argc, char** argv) {
    struct subject {
        vector<string> methods;
        vector<vector<int>> values;
    };
    vector<subject> testData{{{"CustomStack", "push", "push", "pop", "push", "push", "push", "increment", "increment",
                               "pop", "pop", "pop", "pop"},
                              {{3}, {1}, {2}, {}, {2}, {3}, {4}, {5, 100}, {2, 100}, {}, {}, {}, {}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input
     *  ["CustomStack","push","push","pop","push","push","push","increment","increment","pop","pop","pop","pop"]
     *  [[3],[1],[2],[],[2],[3],[4],[5,100],[2,100],[],[],[],[]]
     *  Output
     *  [null,null,null,2,null,null,null,null,null,103,202,201,-1]
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

        CustomStack cCustomStack(testData[i].values[0][0]);
        cout << "Output\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            cout << (j == 0 ? "" : ",");
            if (testData[i].methods[j].compare("CustomStack") == 0) {
                cout << "null";
            } else if (testData[i].methods[j].compare("push") == 0) {
                cCustomStack.push(testData[i].values[j][0]);
                cout << "null";
            } else if (testData[i].methods[j].compare("pop") == 0) {
                int retVal = cCustomStack.pop();
                cout << retVal;
            } else if (testData[i].methods[j].compare("increment") == 0) {
                cCustomStack.increment(testData[i].values[j][0], testData[i].values[j][1]);
                cout << "null";
            }
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
