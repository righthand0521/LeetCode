import logging
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache, lru_cache
from heapq import heapify, heappop, heappush
from itertools import accumulate
from typing import List, Optional


def logging_setting():
    LOG_LEVEL = logging.INFO    # DEBUG, INFO, WARNING, ERROR, CRITICAL
    if __debug__:
        LOG_LEVEL = logging.DEBUG

    logging.basicConfig(
        stream=sys.stderr,
        level=LOG_LEVEL,
        format="%(levelname)-6s %(asctime)s %(module)s:%(funcName)s:%(lineno)-4s %(message)s",
        datefmt='%Y/%m/%d %H:%M:%S')


# https: // leetcode.com/problems/next-greater-numerically-balanced-number/solutions/1537631/next-permutation-vs-dfs/
class Solution:
    def __init__(self):
        self.cnt = [i for i in range(10)]

    def dfs(self, n: int, val: int, sz: int) -> int:
        retVal = 0

        if sz == 0:
            for i in range(1, 10):
                if self.cnt[i] != i and self.cnt[i] != 0:
                    return retVal
            retVal = val if val > n else 0

            return retVal

        for i in range(1, 10):
            if retVal == 0 and self.cnt[i] > 0 and self.cnt[i] <= sz:
                self.cnt[i] -= 1
                retVal = self.dfs(n, val * 10 + i, sz - 1)
                self.cnt[i] += 1

        return retVal

    def nextBeautifulNumber(self, n: int) -> int:
        retVal = 0

        sz = len(str(n))
        retVal = self.dfs(n, 0, sz)
        if retVal == 0:
            retVal = self.dfs(0, 0, sz + 1)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n in [1, 1000, 3000]:
            # /* Example
            #  *  Input: n = 1
            #  *  Output: 22
            #  *
            #  *  Input: n = 1000
            #  *  Output: 1333
            #  *
            #  *  Input: n = 3000
            #  *  Output: 3133
            #  */
            logging.info("Input: n = %s", n)

            retVal = pSolution.nextBeautifulNumber(n)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
