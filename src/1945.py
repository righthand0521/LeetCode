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


class Solution:
    def getLucky(self, s: str, k: int) -> int:
        retVal = 0

        sum = 0
        for c in s:
            translateToInteger = (ord(c) - ord('a') + 1)
            sum += (translateToInteger % 10)
            sum += (translateToInteger // 10)

        retVal = sum
        for _ in range(1, k):
            retVal = 0
            while sum > 0:
                retVal += (sum % 10)
                sum //= 10
            sum = retVal

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s, k in zip(["iiii", "leetcode", "zbax"], [1, 2, 2]):
            # /* Example
            #  *  Input: s = "iiii", k = 1
            #  *  Output: 36
            #  *
            #  *  Input: s = "leetcode", k = 2
            #  *  Output: 6
            #  *
            #  *  Input: s = "zbax", k = 2
            #  *  Output: 8
            #  */
            logging.info("Input: s = \"%s\", k = %s", s, k)

            retVal = pSolution.getLucky(s, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
