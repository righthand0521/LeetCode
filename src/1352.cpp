#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class ProductOfNumbers {
   private:
    // Stores cumulative product of the stream
    vector<int> prefixProduct;
    int size = 0;

   public:
    ProductOfNumbers() {
        // Initialize the product list with 1 to handle multiplication logic
        prefixProduct.push_back(1);
        size = 0;
    }
    void add(int num) {
        if (num == 0) {
            // If num is 0, reset the cumulative products since multiplication with 0 invalidates previous products
            prefixProduct = {1};
            size = 0;
        } else {
            // Append the cumulative product of the current number with the last product
            prefixProduct.push_back(prefixProduct[size] * num);
            size++;
        }
    }
    int getProduct(int k) {
        int retVal = 0;

        // Check if the requested product length exceeds the size of the valid product list
        if (k > size) {
            return retVal;
        }
        // Compute the product of the last k elements using division
        retVal = prefixProduct[size] / prefixProduct[size - k];

        return retVal;
    }
};
/**
 * Your ProductOfNumbers object will be instantiated and called as such:
 * ProductOfNumbers* obj = new ProductOfNumbers();
 * obj->add(num);
 * int param_2 = obj->getProduct(k);
 */

int main(int argc, char **argv) {
    struct subject {
        vector<string> methods;
        vector<vector<int>> val;
    };
    vector<subject> testData{{{"ProductOfNumbers", "add", "add", "add", "add", "add", "getProduct", "getProduct",
                               "getProduct", "add", "getProduct"},
                              {{}, {3}, {0}, {2}, {5}, {4}, {2}, {3}, {4}, {8}, {2}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input
     *  ["ProductOfNumbers","add","add","add","add","add","getProduct","getProduct","getProduct","add","getProduct"]
     *  [[],[3],[0],[2],[5],[4],[2],[3],[4],[8],[2]]
     *  Output
     *  [null,null,null,null,null,null,20,40,0,null,32]
     */

    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            cout << (j == 0 ? "" : ", ") << '"' << testData[i].methods[j] << '"';
        }
        cout << "]\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].val.size(); ++j) {
            cout << (j == 0 ? "" : ", ") << "[";
            for (long unsigned int k = 0; k < testData[i].val[j].size(); ++k) {
                cout << (k == 0 ? "" : ", ") << testData[i].val[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        ProductOfNumbers cProductOfNumbers;
        cout << "Output\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            if (testData[i].methods[j].compare("ProductOfNumbers") == 0) {
                cout << (j == 0 ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("add") == 0) {
                cProductOfNumbers.add(testData[i].val[j][0]);
                cout << (j == 0 ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("getProduct") == 0) {
                int retVal = cProductOfNumbers.getProduct(testData[i].val[j][0]);
                cout << (j == 0 ? "" : ", ") << retVal;
            }
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
