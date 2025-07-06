#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class FindSumPairs {
   private:
    vector<int> nums1;
    vector<int> nums2;
    unordered_map<int, int> frequency;

   public:
    FindSumPairs(vector<int>& nums1, vector<int>& nums2) {
        this->nums1 = nums1;
        this->nums2 = nums2;
        for (int num : nums2) {
            ++frequency[num];
        }
    }
    void add(int index, int val) {
        --frequency[nums2[index]];
        nums2[index] += val;
        ++frequency[nums2[index]];
    }
    int count(int tot) {
        int retVal = 0;

        for (int num : nums1) {
            int value = tot - num;
            if (frequency.count(value)) {
                retVal += frequency[value];
            }
        }

        return retVal;
    }
};
/**
 * Your FindSumPairs object will be instantiated and called as such:
 * FindSumPairs* obj = new FindSumPairs(nums1, nums2);
 * obj->add(index,val);
 * int param_2 = obj->count(tot);
 */

int main(int argc, char** argv) {
    struct subject {
        vector<string> methods;
        vector<vector<int>> nums1;
        vector<vector<int>> nums2;
        vector<int> index;
        vector<int> val;
        vector<int> tot;
    };
    vector<subject> testData{{{"FindSumPairs", "count", "add", "count", "count", "add", "add", "count"},
                              {{1, 1, 2, 2, 2, 3}, {}, {}, {}, {}, {}, {}, {}},
                              {{1, 4, 5, 2, 5, 4}, {}, {}, {}, {}, {}, {}, {}},
                              {0, 0, 3, 0, 0, 0, 1, 0},
                              {0, 0, 2, 0, 0, 1, 1, 0},
                              {0, 7, 0, 8, 4, 0, 0, 7}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input
     *  ["FindSumPairs", "count", "add", "count", "count", "add", "add", "count"]
     *  [[[1, 1, 2, 2, 2, 3], [1, 4, 5, 2, 5, 4]], [7], [3, 2], [8], [4], [0, 1], [1, 1], [7]]
     *  Output
     *  [null, 8, null, 2, 1, null, null, 11]
     */

    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            cout << (j == 0 ? "" : ", ") << '"' << testData[i].methods[j] << '"';
        }
        cout << "]\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            cout << (j == 0 ? "" : ", ") << "[";
            if (testData[i].methods[j].compare("FindSumPairs") == 0) {
                cout << "[";
                for (long unsigned int k = 0; k < testData[i].nums1[j].size(); ++k) {
                    cout << (k == 0 ? "" : ", ") << testData[i].nums1[j][k];
                }
                cout << "], [";
                for (long unsigned int k = 0; k < testData[i].nums2[j].size(); ++k) {
                    cout << (k == 0 ? "" : ", ") << testData[i].nums2[j][k];
                }
                cout << "]";
            } else if (testData[i].methods[j].compare("add") == 0) {
                cout << testData[i].index[j] << ", " << testData[i].val[j];
            } else if (testData[i].methods[j].compare("count") == 0) {
                cout << testData[i].tot[j];
            }
            cout << "]";
        }
        cout << "]\n";

        FindSumPairs cFindSumPairs(testData[i].nums1[0], testData[i].nums2[0]);
        cout << "Output\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            if (testData[i].methods[j].compare("FindSumPairs") == 0) {
                cout << (j == 0 ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("add") == 0) {
                cFindSumPairs.add(testData[i].index[j], testData[i].val[j]);
                cout << (j == 0 ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("count") == 0) {
                int retVal = cFindSumPairs.count(testData[i].tot[j]);
                cout << (j == 0 ? "" : ", ") << retVal;
            }
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
