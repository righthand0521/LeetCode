#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

using namespace std;

struct LazyTag {
    int to_add = 0;

    LazyTag& operator+=(const LazyTag& other) {
        this->to_add += other.to_add;

        return *this;
    }
    bool has_tag() const {
        bool retVal = (to_add != 0);

        return retVal;
    }
    void clear() {
        //
        to_add = 0;
    }
};
struct SegmentTreeNode {
    int min_value = 0;
    int max_value = 0;
    // int data = 0; // only leaf nodes are used, this question does not require it.
    LazyTag lazy_tag;
};
class SegmentTree {
   public:
    int n;
    vector<SegmentTreeNode> tree;

    SegmentTree(const vector<int>& data) : n(data.size()) {
        tree.resize(n * 4 + 1);
        build(data, 1, n, 1);
    }
    void add(int l, int r, int val) {
        LazyTag tag{val};
        update(l, r, tag, 1, n, 1);
    }
    int find_last(int start, int val) {
        int retVal = -1;

        if (start <= n) {
            retVal = find(start, n, val, 1, n, 1);
        }

        return retVal;
    }

   private:
    inline void apply_tag(int i, const LazyTag& tag) {
        tree[i].min_value += tag.to_add;
        tree[i].max_value += tag.to_add;
        tree[i].lazy_tag += tag;
    }
    inline void pushdown(int i) {
        if (tree[i].lazy_tag.has_tag() == true) {
            LazyTag tag = tree[i].lazy_tag;
            apply_tag(i << 1, tag);
            apply_tag(i << 1 | 1, tag);
            tree[i].lazy_tag.clear();
        }
    }
    inline void pushup(int i) {
        tree[i].min_value = std::min(tree[i << 1].min_value, tree[i << 1 | 1].min_value);
        tree[i].max_value = std::max(tree[i << 1].max_value, tree[i << 1 | 1].max_value);
    }
    void build(const vector<int>& data, int l, int r, int i) {
        if (l == r) {
            tree[i].min_value = tree[i].max_value = data[l - 1];
            return;
        }
        int mid = l + ((r - l) >> 1);
        build(data, l, mid, i << 1);
        build(data, mid + 1, r, i << 1 | 1);
        pushup(i);
    }
    void update(int target_l, int target_r, const LazyTag& tag, int l, int r, int i) {
        if ((target_l <= l) && (r <= target_r)) {
            apply_tag(i, tag);
            return;
        }
        pushdown(i);

        int mid = l + ((r - l) >> 1);
        if (target_l <= mid) {
            update(target_l, target_r, tag, l, mid, i << 1);
        }
        if (target_r > mid) {
            update(target_l, target_r, tag, mid + 1, r, i << 1 | 1);
        }
        pushup(i);
    }
    int find(int target_l, int target_r, int val, int l, int r, int i) {
        int retVal = -1;

        if (tree[i].min_value > val || tree[i].max_value < val) {
            return retVal;
        }

        // according to the Intermediate Value Theorem, there must be a solution within this interval.
        if (l == r) {
            retVal = l;
            return retVal;
        }
        pushdown(i);

        int mid = l + ((r - l) >> 1);

        // target_l is definitely less than or equal to r (=n)
        if (target_r >= mid + 1) {
            retVal = find(target_l, target_r, val, mid + 1, r, i << 1 | 1);
            if (retVal != -1) {
                return retVal;
            }
        }

        if (l <= target_r && mid >= target_l) {
            retVal = find(target_l, target_r, val, l, mid, i << 1);
            return retVal;
        }

        return retVal;
    }
};
class Solution {
   private:
    int sgn(int x) {
        int retVal = -1;

        if (x % 2 == 0) {
            retVal = 1;
        }

        return retVal;
    }

   public:
    int longestBalanced(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();

        map<int, queue<int>> occurrences;
        occurrences[nums[0]].push(1);

        vector<int> prefix_sum(numsSize, 0);
        prefix_sum[0] = sgn(nums[0]);
        for (int i = 1; i < numsSize; i++) {
            prefix_sum[i] = prefix_sum[i - 1];
            auto& occ = occurrences[nums[i]];
            if (occ.empty() == true) {
                prefix_sum[i] += sgn(nums[i]);
            }
            occ.push(i + 1);
        }

        SegmentTree seg(prefix_sum);
        for (int i = 0; i < numsSize; i++) {
            retVal = max(retVal, seg.find_last(i + retVal, 0) - i);

            auto next_pos = numsSize + 1;
            occurrences[nums[i]].pop();
            if (occurrences[nums[i]].empty() == false) {
                next_pos = occurrences[nums[i]].front();
            }

            seg.add(i + 1, next_pos - 1, -sgn(nums[i]));
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{2, 5, 4, 3}}, {{3, 2, 2, 5, 4}}, {{1, 2, 3, 2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [2,5,4,3]
     *  Output: 4
     *
     *  Input: nums = [3,2,2,5,4]
     *  Output: 5
     *
     *  Input: nums = [1,2,3,2]
     *  Output: 3
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.longestBalanced(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
