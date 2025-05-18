#include <algorithm>
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   private:
    const int MODULO = 1e9 + 7;

   public:
    int colorTheGrid(int m, int n) {
        int retVal = 0;

        // Hash mapping stores all valid coloration schemes for a single row that meet the requirements
        // The key represents mask, and the value represents the ternary string of mask (stored as a list)
        unordered_map<int, vector<int>> valid;
        // Enumerate masks that meet the requirements within the range [0, 3^m)
        int mask_end = pow(3, m);
        for (int mask = 0; mask < mask_end; ++mask) {
            vector<int> color;
            int mm = mask;
            for (int i = 0; i < m; ++i) {
                color.push_back(mm % 3);
                mm /= 3;
            }

            bool check = true;
            for (int i = 0; i < m - 1; ++i) {
                if (color[i] == color[i + 1]) {
                    check = false;
                    break;
                }
            }
            if (check == true) {
                valid[mask] = move(color);
            }
        }

        // Preprocess all (mask1, mask2) binary tuples, satisfying mask1 and mask2 When adjacent rows,
        // the colors of the two cells in the same column are different
        unordered_map<int, vector<int>> adjacent;
        for (const auto& [mask1, color1] : valid) {
            for (const auto& [mask2, color2] : valid) {
                bool check = true;
                for (int i = 0; i < m; ++i) {
                    if (color1[i] == color2[i]) {
                        check = false;
                        break;
                    }
                }
                if (check == true) {
                    adjacent[mask1].push_back(mask2);
                }
            }
        }

        vector<int> f(mask_end);
        for (const auto& [mask, _] : valid) {
            f[mask] = 1;
        }
        for (int i = 1; i < n; ++i) {
            vector<int> g(mask_end);
            for (const auto& [mask2, _] : valid) {
                for (int mask1 : adjacent[mask2]) {
                    g[mask2] += f[mask1];
                    if (g[mask2] >= MODULO) {
                        g[mask2] -= MODULO;
                    }
                }
            }
            f = move(g);
        }

        for (int num : f) {
            retVal += num;
            if (retVal >= MODULO) {
                retVal -= MODULO;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int m;
        int n;
    };
    vector<subject> testData{{1, 1}, {1, 2}, {5, 5}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: m = 1, n = 1
     *  Output: 3
     *
     *  Input: m = 1, n = 2
     *  Output: 6
     *
     *  Input: m = 5, n = 5
     *  Output: 580986
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: m = " << testData[i].m << ", n = " << testData[i].n << "\n";

        answer = cSolution.colorTheGrid(testData[i].m, testData[i].n);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
