#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool areSentencesSimilar(string sentence1, string sentence2) {
        bool retVal = false;

        vector<string> words1;
        istringstream in1(sentence1);
        string word1;
        while (in1 >> word1) {
            words1.push_back(word1);
        }

        vector<string> words2;
        istringstream in2(sentence2);
        string word2;
        while (in2 >> word2) {
            words2.push_back(word2);
        }

        while ((words1.empty() == false) && (words2.empty() == false) && (words1.front() == words2.front())) {
            words1.erase(words1.begin());
            words2.erase(words2.begin());
        }

        while ((words1.empty() == false) && (words2.empty() == false) && (words1.back() == words2.back())) {
            words1.pop_back();
            words2.pop_back();
        }

        if ((words1.empty() == true) || (words2.empty() == true)) {
            retVal = true;
        }

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        string sentence1;
        string sentence2;
    };
    vector<subject> testData{{"My name is Haley", "My Haley"},
                             {"of", "A lot of words"},
                             {"Eating right now", "Eating"},
                             {"Luky", "Lucccky"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: sentence1 = "My name is Haley", sentence2 = "My Haley"
     *  Output: true
     *
     *  Input: sentence1 = "of", sentence2 = "A lot of words"
     *  Output: false
     *
     *  Input: sentence1 = "Eating right now", sentence2 = "Eating"
     *  Output: true
     *
     *  Input: sentence1 = "Luky", sentence2 = "Lucccky"
     *  Output: false
     */

    Solution cSolution;
    bool answer = false;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: sentence1 = \"" << testData[i].sentence1;
        cout << ", sentence2 = \"" << testData[i].sentence2 << "\"\n";

        answer = cSolution.areSentencesSimilar(testData[i].sentence1, testData[i].sentence2);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
