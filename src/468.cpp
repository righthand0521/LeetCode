#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
#define RETURN_IPV4 "IPv4"
#define RETURN_IPV6 "IPv6"
#define RETURN_NEITHER "Neither"
   public:
    string validIPAddress(string queryIP) {
        string retVal(RETURN_NEITHER);

        int len = queryIP.length();
        if (len == 0) {
            return retVal;
        }

        int last;
        long unsigned int cur;
        int i;
        long unsigned int j;

        if (queryIP.find('.') != string::npos) {
            last = -1;

            for (i = 0; i < 4; ++i) {
                if (i == 3) {
                    cur = queryIP.size();
                } else {
                    cur = queryIP.find('.', last + 1);
                }
                if (cur == string::npos) {
                    return retVal;
                } else if (cur - last - 1 < 1 || cur - last - 1 > 3) {
                    return retVal;
                }

                int addr = 0;
                for (j = last + 1; j < cur; ++j) {
                    if (!isdigit(queryIP[j])) {
                        return retVal;
                    }
                    addr = addr * 10 + (queryIP[j] - '0');
                }
                if (addr > 255) {
                    return retVal;
                } else if ((addr > 0) && (queryIP[last + 1] == '0')) {
                    return retVal;
                } else if ((addr == 0) && (cur - last - 1 > 1)) {
                    return retVal;
                }

                last = cur;
            }

            return RETURN_IPV4;
        }

        last = -1;
        for (i = 0; i < 8; ++i) {
            if (i == 7) {
                cur = queryIP.size();
            } else {
                cur = queryIP.find(':', last + 1);
            }
            if (cur == string::npos) {
                return retVal;
            } else if ((cur - last - 1 < 1) || (cur - last - 1 > 4)) {
                return retVal;
            }

            for (j = last + 1; j < cur; ++j) {
                if ((!isdigit(queryIP[j])) && (!(('a' <= tolower(queryIP[j])) && (tolower(queryIP[j]) <= 'f')))) {
                    return retVal;
                }
            }

            last = cur;
        }

        return RETURN_IPV6;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string queryIP;
    };
    vector<subject> testData{{"172.16.254.1"},         {"2001:0db8:85a3:0:0:8A2E:0370:7334"},
                             {"256.256.256.256"},      {"2001:0db8:85a3:0:0:8A2E:0370:7334:"},
                             {"1abcde.4.5.6"},         {""},
                             {"2001:4860:4860::8888"}, {"20EE:FGb8:85a3:0:0:8A2E:0370:7334"}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: queryIP = \"" << testData[i].queryIP << "\"\n";

        answer = cSolution.validIPAddress(testData[i].queryIP);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
