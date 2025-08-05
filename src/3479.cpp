#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   private:
    int segmentTree[400007];  // n == fruits.length == baskets.length, 1 <= n <= 10 ^ 5 .
    vector<int> baskets;

    void build(int p, int left, int right) {
        if (left == right) {
            segmentTree[p] = baskets[left];
            return;
        }

        int middle = (left + right) >> 1;
        build((p << 1), left, middle);
        build((p << 1) | 1, middle + 1, right);
        segmentTree[p] = max(segmentTree[(p << 1)], segmentTree[(p << 1) | 1]);
    }
    int query(int p, int left, int right, int ql, int qr) {
        int retVal = 0;

        if ((ql > right) || (qr < left)) {
            retVal = numeric_limits<int>::min();
        } else if ((ql <= left) && (right <= qr)) {
            retVal = segmentTree[p];
        } else {
            int middle = (left + right) >> 1;
            retVal = max(query(p << 1, left, middle, ql, qr), query(p << 1 | 1, middle + 1, right, ql, qr));
        }

        return retVal;
    }
    void update(int p, int left, int right, int pos, int val) {
        if (left == right) {
            segmentTree[p] = val;
            return;
        }

        int middle = (left + right) >> 1;
        if (pos <= middle) {
            update((p << 1), left, middle, pos, val);
        } else {
            update((p << 1) | 1, middle + 1, right, pos, val);
        }
        segmentTree[p] = max(segmentTree[(p << 1)], segmentTree[(p << 1) | 1]);
    }

   public:
    int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {
        int retVal = 0;

        this->baskets = baskets;
        int fruitsSize = fruits.size();
        int basketsSize = baskets.size();
        if (basketsSize == 0) {
            retVal = fruitsSize;
            return retVal;
        }

        build(1, 0, basketsSize - 1);

        for (int i = 0; i < fruitsSize; i++) {
            int res = -1;
            int left = 0;
            int right = basketsSize - 1;
            while (left <= right) {
                int middle = (left + right) >> 1;

                if (query(1, 0, basketsSize - 1, 0, middle) >= fruits[i]) {
                    res = middle;
                    right = middle - 1;
                } else {
                    left = middle + 1;
                }
            }

            if ((res != -1) && (baskets[res] >= fruits[i])) {
                update(1, 0, basketsSize - 1, res, numeric_limits<int>::min());
            } else {
                retVal++;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> fruits;
        vector<int> baskets;
    };
    vector<subject> testData{{{4, 2, 5}, {3, 5, 4}}, {{3, 6, 1}, {6, 4, 7}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: fruits = [4,2,5], baskets = [3,5,4]
     *  Output: 1
     *
     *  Input: fruits = [3,6,1], baskets = [6,4,7]
     *  Output: 0
     */

    Solution cSolution;
    double answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: fruits = [";
        for (long unsigned int j = 0; j < testData[i].fruits.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].fruits[j];
        }
        cout << "], baskets = [";
        for (long unsigned int j = 0; j < testData[i].baskets.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].baskets[j];
        }
        cout << "]\n";

        answer = cSolution.numOfUnplacedFruits(testData[i].fruits, testData[i].baskets);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
