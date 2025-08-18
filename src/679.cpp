#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    static constexpr int TARGET = 24;
    static constexpr double EPSILON = 1e-6;
    enum Operation { ADD = 0, MULTIPLY = 1, SUBTRACT = 2, DIVIDE = 3 };

    bool backtracking(vector<double>& cards) {
        bool retVal = false;

        int cardsSize = cards.size();
        if (cardsSize == 0) {
            return retVal;
        } else if (cardsSize == 1) {
            retVal = fabs(cards[0] - TARGET) < EPSILON;
            return retVal;
        }

        for (int i = 0; i < cardsSize; i++) {
            for (int j = 0; j < cardsSize; j++) {
                if (i == j) {
                    continue;
                }

                vector<double> copyDoubleCards = vector<double>();
                for (int k = 0; k < cardsSize; k++) {
                    if ((k != i) && (k != j)) {
                        copyDoubleCards.emplace_back(cards[k]);
                    }
                }

                for (int k = 0; k < 4; k++) {
                    if ((k < 2) && (i > j)) {
                        continue;
                    }

                    if (k == ADD) {
                        copyDoubleCards.emplace_back(cards[i] + cards[j]);
                    } else if (k == MULTIPLY) {
                        copyDoubleCards.emplace_back(cards[i] * cards[j]);
                    } else if (k == SUBTRACT) {
                        copyDoubleCards.emplace_back(cards[i] - cards[j]);
                    } else if (k == DIVIDE) {
                        if (fabs(cards[j]) < EPSILON) {
                            continue;
                        }
                        copyDoubleCards.emplace_back(cards[i] / cards[j]);
                    }

                    if (backtracking(copyDoubleCards) == true) {
                        retVal = true;
                        return retVal;
                    }
                    copyDoubleCards.pop_back();
                }
            }
        }

        return retVal;
    }

   public:
    bool judgePoint24(vector<int>& cards) {
        bool retVal = false;

        vector<double> doubleCards;
        for (const int& card : cards) {
            doubleCards.emplace_back(static_cast<double>(card));
        }
        retVal = backtracking(doubleCards);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> cards;
    };
    vector<subject> testData{{{4, 1, 8, 7}}, {{1, 2, 1, 2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: cards = [4,1,8,7]
     *  Output: true
     *
     *  Input: cards = [1,2,1,2]
     *  Output: false
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].cards.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].cards[j];
        }
        cout << "]\n";

        answer = cSolution.judgePoint24(testData[i].cards);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
