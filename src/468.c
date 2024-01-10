#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RETURN_IPV4 "IPv4"
#define RETURN_IPV6 "IPv6"
#define RETURN_NEITHER "Neither"
#if 0  // inet_pton - convert IPv4 and IPv6 addresses from text to binary form
#include <arpa/inet.h>

char* validIPAddress(char* queryIP) {
    char buf[16];
    memset(buf, 0, sizeof(buf));

    if (inet_pton(AF_INET, queryIP, buf)) {
        return RETURN_IPV4;
    } else if (inet_pton(AF_INET6, queryIP, buf)) {
        return RETURN_IPV6;
    }

    return RETURN_NEITHER;
}
#else
char* validIPAddress(char* queryIP) {
    char* pRetVal = RETURN_NEITHER;

    int len = strlen(queryIP);
    if (len == 0) {
        return pRetVal;
    }

    int n;
    char x[8][len];
    char extra[len];
    int num;
    int i;

    // x1.x2.x3.x4
    memset(x, 0, sizeof(x));
    memset(extra, 0, sizeof(extra));
    n = sscanf(queryIP, "%[^.].%[^.].%[^.].%[^.]%s", x[0], x[1], x[2], x[3], extra);
    if (n == 4) {
        for (i = 0; i < n; ++i) {
            if ((strlen(x[i]) > 1) && (x[i][0] == '0')) {
                return pRetVal;
            }

            memset(extra, 0, sizeof(extra));
            if (sscanf(x[i], "%d%s", &num, extra) != 1) {
                return pRetVal;
            }
            if ((num < 0) || (num > 255)) {
                return pRetVal;
            }
        }
        pRetVal = RETURN_IPV4;
        return pRetVal;
    }

    // x1:x2:x3:x4:x5:x6:x7:x8
    memset(x, 0, sizeof(x));
    memset(extra, 0, sizeof(extra));
    n = sscanf(queryIP, "%[^:]:%[^:]:%[^:]:%[^:]:%[^:]:%[^:]:%[^:]:%[^:]%s", x[0], x[1], x[2], x[3], x[4], x[5], x[6],
               x[7], extra);
    if (n == 8) {
        for (i = 0; i < n; ++i) {
            if (strlen(x[i]) > 4) {
                return pRetVal;
            }

            memset(extra, 0, sizeof(extra));
            if (sscanf(x[i], "%x%s", &num, extra) != 1) {
                return pRetVal;
            }
            if ((num < 0) || (num > 65535)) {
                return pRetVal;
            }
        }
        pRetVal = RETURN_IPV6;
        return pRetVal;
    }

    return pRetVal;
}
#endif

int main(int argc, char** argv) {
    struct testCaseType {
        char* queryIP;
    } testCase[] = {{"172.16.254.1"},         {"2001:0db8:85a3:0:0:8A2E:0370:7334"},
                    {"256.256.256.256"},      {"2001:0db8:85a3:0:0:8A2E:0370:7334:"},
                    {"1abcde.4.5.6"},         {""},
                    {"2001:4860:4860::8888"}, {"20EE:FGb8:85a3:0:0:8A2E:0370:7334"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: queryIP = \"%s\"\n", testCase[i].queryIP);

        pAnswer = validIPAddress(testCase[i].queryIP);
        printf("Output: %s\n", pAnswer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
