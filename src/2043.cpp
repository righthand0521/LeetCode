#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Bank {
   private:
    vector<long long> balance;
    int balanceSize;

   public:
    Bank(vector<long long>& balance) : balance(balance) {
        //
        balanceSize = balance.size();
    }
    bool transfer(int account1, int account2, long long money) {
        bool retVal = false;

        if ((balanceSize < account1) || (balanceSize < account2)) {
            return retVal;
        } else if (balance[account1 - 1] < money) {
            return retVal;
        }

        balance[account1 - 1] -= money;
        balance[account2 - 1] += money;
        retVal = true;

        return retVal;
    }
    bool deposit(int account, long long money) {
        bool retVal = false;

        if (balanceSize < account) {
            return retVal;
        }

        balance[account - 1] += money;
        retVal = true;

        return retVal;
    }
    bool withdraw(int account, long long money) {
        bool retVal = false;

        if (balanceSize < account) {
            return retVal;
        } else if (balance[account - 1] < money) {
            return retVal;
        }

        balance[account - 1] -= money;
        retVal = true;

        return retVal;
    }
};
/**
 * Your Bank object will be instantiated and called as such:
 * Bank* obj = new Bank(balance);
 * bool param_1 = obj->transfer(account1,account2,money);
 * bool param_2 = obj->deposit(account,money);
 * bool param_3 = obj->withdraw(account,money);
 */

int main(int argc, char** argv) {
    struct subject {
        vector<string> methods;
        vector<vector<long long>> values;
    };
    vector<subject> testData{{{"Bank", "withdraw", "transfer", "deposit", "transfer", "withdraw"},
                              {{10, 100, 20, 50, 30}, {3, 10}, {5, 1, 20}, {5, 20}, {3, 4, 15}, {10, 50}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input
     *  ["Bank", "withdraw", "transfer", "deposit", "transfer", "withdraw"]
     *  [[[10, 100, 20, 50, 30]], [3, 10], [5, 1, 20], [5, 20], [3, 4, 15], [10, 50]]
     *  Output
     *  [null, true, true, true, false, false]
     */

    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            cout << (j == 0 ? "" : ", ") << '"' << testData[i].methods[j] << '"';
        }
        cout << "]\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].values.size(); ++j) {
            cout << (j == 0 ? "" : ", ") << "[";
            for (long unsigned int k = 0; k < testData[i].values[j].size(); ++k) {
                cout << (k == 0 ? "" : ", ") << testData[i].values[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        Bank cBank(testData[i].values[0]);
        cout << "Output\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            if (testData[i].methods[j].compare("Bank") == 0) {
                cout << (j == 0 ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("transfer") == 0) {
                bool retVal =
                    cBank.transfer(testData[i].values[j][0], testData[i].values[j][1], testData[i].values[j][2]);
                cout << (j == 0 ? "" : ", ") << (retVal == true ? "true" : "false");
            } else if (testData[i].methods[j].compare("deposit") == 0) {
                bool retVal = cBank.deposit(testData[i].values[j][0], testData[i].values[j][1]);
                cout << (j == 0 ? "" : ", ") << (retVal == true ? "true" : "false");
            } else if (testData[i].methods[j].compare("withdraw") == 0) {
                bool retVal = cBank.withdraw(testData[i].values[j][0], testData[i].values[j][1]);
                cout << (j == 0 ? "" : ", ") << (retVal == true ? "true" : "false");
            }
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
