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
    def findMaxForm(self, strs: List[str], m: int, n: int) -> int:
        retVal = 0

        strsSize = len(strs)

        bitsCount = [[0, 0] for _ in range(strsSize)]
        for i in range(strsSize):
            for c in strs[i]:
                if c == '0':
                    bitsCount[i][0] += 1
                else:
                    bitsCount[i][1] += 1

        dp = [[0] * (n + 1) for _ in range(m + 1)]
        for i in range(strsSize):
            for j in range(m, bitsCount[i][0] - 1, -1):
                for k in range(n, bitsCount[i][1] - 1, -1):
                    dp[j][k] = max(dp[j][k], dp[j - bitsCount[i][0]][k - bitsCount[i][1]] + 1)
        retVal = dp[m][n]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for strs, m, n in [[["10", "0001", "111001", "1", "0"], 5, 3], [["10", "0", "1"], 1, 1]]:
            # /* Example
            #  *  Input: strs = ["10","0001","111001","1","0"], m = 5, n = 3
            #  *  Output: 4
            #  *
            #  *  Input: strs = ["10","0","1"], m = 1, n = 1
            #  *  Output: 2
            #  */
            logging.info("Input: strs = %s, m = %d, n = %d", strs, m, n)

            retVal = pSolution.findMaxForm(strs, m, n)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
