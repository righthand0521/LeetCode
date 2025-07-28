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
    def calc(self, x: int) -> int:
        retVal = 0

        if x == 1:
            retVal = 1
        elif x < 10:
            retVal = 2
        elif x < 100:
            retVal = 3
        else:
            retVal = 4

        return retVal

    def getLengthOfOptimalCompression(self, s: str, k: int) -> int:
        retVal = 0

        sSize = len(s)

        dp = [[10**9] * (k + 1) for _ in range(sSize + 1)]
        dp[0][0] = 0

        for x in range(1, sSize + 1):
            for y in range(min(k, x) + 1):
                if y > 0:
                    dp[x][y] = dp[x - 1][y - 1]

                same = 0
                diff = 0
                for z in range(x, 0, -1):
                    if s[z - 1] == s[x - 1]:
                        same += 1
                        value = dp[z - 1][y - diff] + self.calc(same)
                        dp[x][y] = min(dp[x][y], value)
                    else:
                        diff += 1
                        if diff > y:
                            break

        retVal = dp[sSize][k]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s, k in zip(["aaabcccd", "aabbaa", "aaaaaaaaaaa"], [2, 2, 0]):
            # /* Example
            #  *  Input: s = "aaabcccd", k = 2
            #  *  Output: 4
            #  *
            #  *  Input: s = "aabbaa", k = 2
            #  *  Output: 2
            #  *
            #  *  Input: s = "aaaaaaaaaaa", k = 0
            #  *  Output: 3
            #  */
            logging.info("Input: s = \"%s\", k = %s", s, k)

            retVal = pSolution.getLengthOfOptimalCompression(s, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
