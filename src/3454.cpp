#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

class SegmentTree {
   private:
    vector<int> count;
    vector<int> covered;
    vector<int> xs;
    int n;

    void modify(int qleft, int qright, int qval, int left, int right, int pos) {
        if (xs[right + 1] <= qleft || xs[left] >= qright) {
            return;
        }

        if ((qleft <= xs[left]) && (xs[right + 1] <= qright)) {
            count[pos] += qval;
        } else {
            int middle = (left + right) / 2;
            modify(qleft, qright, qval, left, middle, pos * 2 + 1);
            modify(qleft, qright, qval, middle + 1, right, pos * 2 + 2);
        }

        if (count[pos] > 0) {
            covered[pos] = xs[right + 1] - xs[left];
        } else {
            if (left == right) {
                covered[pos] = 0;
            } else {
                covered[pos] = covered[pos * 2 + 1] + covered[pos * 2 + 2];
            }
        }
    }

   public:
    SegmentTree(vector<int>& xs_) : xs(xs_) {
        n = xs.size() - 1;
        count.resize(4 * n, 0);
        covered.resize(4 * n, 0);
    }
    void update(int qleft, int qright, int qval) {
        //
        modify(qleft, qright, qval, 0, n - 1, 0);
    }
    int query() {
        int retVal = covered[0];

        return retVal;
    }
};
class Solution {
   public:
    double separateSquares(vector<vector<int>>& squares) {
        double retVal = 0;

        vector<tuple<int, int, int, int>> events;
        set<int> xsSet;
        for (auto& sq : squares) {
            int x = sq[0];
            int y = sq[1];
            int l = sq[2];
            int xr = x + l;
            events.emplace_back(y, 1, x, xr);
            events.emplace_back(y + l, -1, x, xr);
            xsSet.insert(x);
            xsSet.insert(xr);
        }
        // sort events by y-coordinate
        sort(events.begin(), events.end());
        // discrete coordinates
        vector<int> xs(xsSet.begin(), xsSet.end());
        // initialize the segment tree
        SegmentTree segTree(xs);

        vector<double> psum;
        vector<int> widths;
        double totalarea = 0.0;
        int prev = get<0>(events[0]);

        // scan: calculate total area and record intermediate states
        for (auto& [y, delta, xl, xr] : events) {
            int len = segTree.query();
            totalarea += (1LL * len * (y - prev));
            segTree.update(xl, xr, delta);
            // record prefix sums and widths
            psum.push_back(totalarea);
            widths.push_back(segTree.query());
            prev = y;
        }

        // calculate the target area (half rounded up)
        long long target = (long long)(totalarea + 1) / 2;
        // find the first position greater than or equal to target using binary search
        int i = lower_bound(psum.begin(), psum.end(), target) - psum.begin() - 1;
        // get the corresponding area, width, and height
        double area = psum[i];
        int width = widths[i];
        int height = get<0>(events[i]);

        retVal = height + (totalarea - area * 2) / (width * 2.0);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> squares;
    };
    vector<subject> testData{{{{0, 0, 1}, {2, 2, 1}}}, {{{0, 0, 2}, {1, 1, 1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: squares = [[0,0,1],[2,2,1]]
     *  Output: 1.00000
     *
     *  Input: squares = [[0,0,2],[1,1,1]]
     *  Output: 1.00000
     */

    Solution cSolution;
    double answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: squares = [";
        for (long unsigned int j = 0; j < testData[i].squares.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].squares[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].squares[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.separateSquares(testData[i].squares);
        cout.setf(ios::fixed);
        cout.precision(5);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
