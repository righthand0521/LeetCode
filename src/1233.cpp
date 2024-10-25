#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<string> removeSubfolders(vector<string>& folder) {
        vector<string> retVal;

        // Sort the folders alphabetically
        sort(folder.begin(), folder.end());

        // Initialize the retVal vector and add the first folder
        retVal.push_back(folder[0]);

        // Iterate through each folder and check if it's a sub-folder of the last added folder in the retVal
        int folderSize = folder.size();
        for (int i = 1; i < folderSize; i++) {
            string lastFolder = retVal.back();
            lastFolder += '/';

            // Check if the current folder starts with the last added folder path
            int lastFolderSize = lastFolder.size();
            if (folder[i].compare(0, lastFolderSize, lastFolder) != 0) {
                retVal.push_back(folder[i]);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> folder;
    };
    vector<subject> testData{
        {{"/a", "/a/b", "/c/d", "/c/d/e", "/c/f"}}, {{"/a", "/a/b/c", "/a/b/d"}}, {{"/a/b/c", "/a/b/ca", "/a/b/d"}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: folder = ["/a","/a/b","/c/d","/c/d/e","/c/f"]
     *  Output: ["/a","/c/d","/c/f"]
     *
     *  Input: folder = ["/a","/a/b/c","/a/b/d"]
     *  Output: ["/a"]
     *
     *  Input: folder = ["/a/b/c","/a/b/ca","/a/b/d"]
     *  Output: ["/a/b/c","/a/b/ca","/a/b/d"]
     */

    Solution cSolution;
    vector<string> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: folder = [";
        for (long unsigned int j = 0; j < testData[i].folder.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].folder[j] << "\"";
        }
        cout << "]\n";

        answer = cSolution.removeSubfolders(testData[i].folder);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << answer[j] << "\"";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
