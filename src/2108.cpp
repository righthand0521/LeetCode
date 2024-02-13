#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool isPalindrome(string word) {
        bool retVal = true;

        int left = 0;
        int right = word.size() - 1;
        while (left < right) {
            if (word[left++] != word[right--]) {
                retVal = false;
                break;
            }
        }

        return retVal;
    }
    string firstPalindrome(vector<string>& words) {
        string retVal = "";

        for (string word : words) {
            if (isPalindrome(word) == true) {
                retVal = word;
                break;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> words;
    };
    vector<subject> testData{
        {{"abc", "car", "ada", "racecar", "cool"}}, {{"notapalindrome", "racecar"}}, {{"def", "ghi"}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: words = ["abc","car","ada","racecar","cool"]
     *  Output: "ada"
     *
     *  Input: words = ["notapalindrome","racecar"]
     *  Output: "racecar"
     *
     *  Input: words = ["def","ghi"]
     *  Output: ""
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: words = [";
        for (long unsigned int j = 0; j < testData[i].words.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].words[j] << "\"";
        }
        cout << "]\n";

        answer = cSolution.firstPalindrome(testData[i].words);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
