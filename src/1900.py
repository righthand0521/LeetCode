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
    @cache
    def dp(self, n: int, f: int, s: int) -> List[int]:
        retVal = []

        if f + s == n + 1:
            retVal = [1, 1]
            return retVal

        # F(n,f,s)=F(n,n+1-s,n+1-f)
        if f + s > n + 1:
            retVal = self.dp(n, n + 1 - s, n + 1 - f)
            return retVal

        earliest = float("inf")
        latest = float("-inf")
        nHalf = (n + 1) // 2

        if s <= nHalf:  # s On the left or in the middle
            for i in range(f):
                for j in range(s - f):
                    tmp = self.dp(nHalf, i + 1, i + j + 2)
                    earliest = min(earliest, tmp[0])
                    latest = max(latest, tmp[1])
        else:  # s on the right
            sPrime = n + 1 - s
            middle = (n - 2 * sPrime + 1) // 2
            for i in range(f):
                for j in range(sPrime - f):
                    tmp = self.dp(nHalf, i + 1, i + j + middle + 2)
                    earliest = min(earliest, tmp[0])
                    latest = max(latest, tmp[1])

        retVal = [earliest + 1, latest + 1]

        return retVal

    def earliestAndLatest(self, n: int, firstPlayer: int, secondPlayer: int) -> List[int]:
        retVal = []

        # F(n,f,s) = F(n,s,f)
        if firstPlayer > secondPlayer:
            firstPlayer, secondPlayer = secondPlayer, firstPlayer

        retVal = self.dp(n, firstPlayer, secondPlayer)
        self.dp.cache_clear()

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, firstPlayer, secondPlayer in [[11, 2, 4], [5, 1, 5]]:
            # /* Example
            #  *  Input: n = 11, firstPlayer = 2, secondPlayer = 4
            #  *  Output: [3,4]
            #  *
            #  *  Input: n = 5, firstPlayer = 1, secondPlayer = 5
            #  *  Output: [1,1]
            #  */
            logging.info("Input: n = %s, firstPlayer = %s, secondPlayer = %s", n, firstPlayer, secondPlayer)

            retVal = pSolution.earliestAndLatest(n, firstPlayer, secondPlayer)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
