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
    def __init__(self):
        self.MODULO = 10 ** 9 + 7

    def numFactoredBinaryTrees(self, arr: List[int]) -> int:
        retVal = 0

        arr.sort()

        dp = {}
        for index, a in enumerate(arr):
            dp[a] = 1

            for b in arr[0:index]:
                if a % b != 0:
                    continue

                key = int(a/b)
                if key in dp:
                    dp[a] += dp[b] * dp[key]

        retVal = sum(dp.values()) % (self.MODULO)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for arr in [[2, 4], [2, 4, 5, 10]]:
            # /* Example
            #  *  Input: arr = [2,4]
            #  *  Output: 3
            #  *
            #  *  Input: arr = [2,4,5,10]
            #  *  Output: 7
            #  */
            logging.info("Input: arr = %s", arr)

            retVal = pSolution.numFactoredBinaryTrees(arr)
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
