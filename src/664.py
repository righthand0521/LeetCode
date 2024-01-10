import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop


def logging_setting():
    LOG_LEVEL = logging.INFO    # DEBUG, INFO, WARNING, ERROR, CRITICAL
    if __debug__:
        LOG_LEVEL = logging.DEBUG

    logging.basicConfig(
        stream=sys.stderr,
        level=LOG_LEVEL,
        format="%(levelname)-6s %(asctime)s %(module)s:%(funcName)s:%(lineno)-4s %(message)s",
        datefmt='%Y/%m/%d %H:%M:%S')


class Solution:
    def strangePrinter(self, s: str) -> int:
        retVal = 0

        # /* https://leetcode.cn/problems/strange-printer/solutions/792309/xin-shou-pian-cong-xiao-wen-ti-zai-dao-q-qifh/
        #  *  s[i] == s[i]: dp[i][j] = dp[i][j-1]
        #  *  s[i] != s[j]: dp[i][j] = min(dp[i][i] + dp[i+1][j], dp[i][i+1] + dp[i+1][j], ..., dp[i][j-1] + dp[j-1][j])
        #  *
        #  *  Example: Input: s = "abab", Output: 3.
        #  *      0 1 2 3 |   0 1 2 3 |   0 1 2 3 |   0 1 2 3 |   0 1 2 3
        #  *      a b a b |   a b a b |   a b a b |   a b a b |   a b a b    dp[0][0] + dp[1][3] = 1 + 2 = 3
        #  *  0 a 0 0 0 0 | a 1 0 0 0 | a 1 2 0 0 | a 1 2 2 0 | a 1 2 2 3 -> dp[0][1] + dp[2][3] = 2 + 2 = 4
        #  *  1 b 0 0 0 0 | b 0 1 0 0 | b 0 1 2 0 | b 0 1 2 2 | b 0 1 2 2    dp[0][2] + dp[3][3] = 2 + 1 = 3
        #  *  2 a 0 0 0 0 | a 0 0 1 0 | a 0 0 1 2 | a 0 0 1 2 | a 0 0 1 2
        #  *  3 b 0 0 0 0 | b 0 0 0 1 | b 0 0 0 1 | b 0 0 0 1 | b 0 0 0 1
        #  */
        sSize = len(s)
        dp = [[0 for i in range(sSize)] for _ in range(sSize)]

        for i in range(sSize-1, -1, -1):
            dp[i][i] = 1
            for j in range(i+1, sSize):
                if s[i] == s[j]:
                    dp[i][j] = dp[i][j-1]
                else:
                    minValue = 2**31 - 1
                    for k in range(i, j):
                        minValue = min(minValue, dp[i][k]+dp[k+1][j])
                    dp[i][j] = minValue
        # for i in dp:
        #     print(' '.join(map(str, i)))
        retVal = dp[0][sSize-1]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["aaabbb", "aba", "abab"]:
            # /* Example
            #  *  Input: s = "aaabbb"
            #  *  Output: 2
            #  *
            #  *  Input: s = "aba"
            #  *  Output: 2
            #  *
            #  *  Input: s = "abab"
            #  *  Output: 3
            #  */
            logging.info("Input: s = \"%s\"", s)

            retVal = pSolution.strangePrinter(s)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass

    sys.exit(0)
