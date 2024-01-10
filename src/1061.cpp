﻿#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
// s1, s2, and baseStr consist of lowercase English letters.
#define MAX_UNION_FIND (26)
    array<int, MAX_UNION_FIND> UnionFind;

    int find(int idx) {
        while (UnionFind[idx] != idx) {
            idx = UnionFind[idx];
        }

        return idx;
    }
    void join(int idx1, int idx2) {
        int root1 = find(idx1);
        int root2 = find(idx2);
        if (root1 == root2) {
            return;
        }

        if (root1 <= root2) {
            UnionFind[root2] = root1;
        } else {
            UnionFind[root1] = root2;
        }
    }

    string smallestEquivalentString(string s1, string s2, string baseStr) {
        string retVal;

        for (long unsigned int i = 0; i < MAX_UNION_FIND; ++i) {
            UnionFind[i] = i;
        }

        for (long unsigned int i = 0; i < s1.length(); ++i) {
            join(s1[i] - 'a', s2[i] - 'a');
        }

        for (char c : baseStr) {
            retVal += (char)(find((c - 'a')) + 'a');
        }

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        string s1;
        string s2;
        string baseStr;
    };
    vector<subject> testData{
        {"parker", "morris", "parser"}, {"hello", "world", "hold"}, {"leetcode", "programs", "sourcecode"}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s1 = \"" << testData[i].s1 << "\"";
        cout << ", s2 = \"" << testData[i].s2 << "\"";
        cout << ", baseStr = \"" << testData[i].baseStr << "\"\n";

        answer = cSolution.smallestEquivalentString(testData[i].s1, testData[i].s2, testData[i].baseStr);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
