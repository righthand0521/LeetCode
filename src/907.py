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

    def sumSubarrayMins(self, arr: List[int]) -> int:
        retVal = 0

        arrSize = len(arr)

        monoStack = []
        dp = [0] * arrSize
        for idx, value in enumerate(arr):
            while monoStack and arr[monoStack[-1]] > value:
                monoStack.pop()

            key = idx + 1
            if monoStack:
                key = idx - monoStack[-1]

            dp[idx] = key * value
            if monoStack:
                dp[idx] += dp[idx - key]

            monoStack.append(idx)

            retVal = (retVal + dp[idx]) % self.MODULO

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for arr in [[3, 1, 2, 4], [11, 81, 94, 43, 3]]:
            # /* Example
            #  *  Input: arr = [3,1,2,4]
            #  *  Output: 17
            #  *
            #  *  Input: arr = [11,81,94,43,3]
            #  *  Output: 444
            #  */
            logging.info("Input: arr = %s", arr)

            retVal = pSolution.sumSubarrayMins(arr)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
