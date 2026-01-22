#include <algorithm>
#include <bitset>
#include <iostream>
#include <list>
#include <queue>
#include <vector>

using namespace std;

const int MAX_NODE = 100005;
struct Node {
    long long value;
    int left;
};
using ListIt = std::list<Node>::iterator;
struct Pair {
    ListIt first;
    ListIt second;
    int firstLeft;
    int secondLeft;
    long long cost;

    Pair() {}
    Pair(ListIt fi, ListIt se, long long cost)
        : first(fi), second(se), firstLeft(fi->left), secondLeft(se->left), cost(cost) {}
};
struct ComparePair {
    bool operator()(const Pair& a, const Pair& b) {
        bool retVal = (a.firstLeft > b.firstLeft);

        if (a.cost != b.cost) {
            retVal = (a.cost > b.cost);
        }

        return retVal;
    }
};
class Solution {
   public:
    int minimumPairRemoval(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();

        list<Node> list;
        list.push_back({nums[0], 0});
        priority_queue<Pair, vector<Pair>, ComparePair> pq;
        int decreaseCount = 0;
        for (int i = 1; i < numsSize; ++i) {
            list.push_back({nums[i], (int)i});

            auto current = prev(list.end());
            auto previous = prev(current);

            pq.push({previous, current, previous->value + current->value});

            if (nums[i - 1] > nums[i]) {
                decreaseCount++;
            }
        }

        bitset<MAX_NODE> merged;
        while ((decreaseCount > 0) && (pq.empty() == false)) {
            auto top = pq.top();
            pq.pop();

            if ((merged[top.firstLeft] == true) || (merged[top.secondLeft] == true)) {
                continue;
            }

            auto first = top.first;
            auto second = top.second;
            auto cost = top.cost;
            if (first->value + second->value != cost) {
                continue;
            }

            retVal++;

            if (first->value > second->value) {
                decreaseCount--;
            }

            ListIt previous = (first == list.begin()) ? list.end() : prev(first);
            ListIt next = std::next(second);
            if (previous != list.end()) {
                if ((previous->value > first->value) && (previous->value <= cost)) {
                    decreaseCount--;
                }
                if ((previous->value <= first->value) && (previous->value > cost)) {
                    decreaseCount++;
                }
                pq.push({previous, first, previous->value + cost});
            }

            if (next != list.end()) {
                if ((second->value > next->value) && (cost <= next->value)) {
                    decreaseCount--;
                }
                if ((second->value <= next->value) && (cost > next->value)) {
                    decreaseCount++;
                }
                pq.push({first, next, cost + next->value});
            }

            first->value = cost;
            merged[second->left] = 1;
            list.erase(second);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{5, 2, 3, 1}}, {{1, 2, 2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [5,2,3,1]
     *  Output: 2
     *
     *  Input: nums = [1,2,2]
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.minimumPairRemoval(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
