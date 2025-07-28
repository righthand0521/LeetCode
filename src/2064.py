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
    def canDistribute(self, x: int, quantities: List[int], n: int) -> bool:
        retVal = False

        quantitiesSize = len(quantities)

        i = 0
        remaining = quantities[i]
        for _ in range(n):
            if remaining > x:
                remaining -= x
                continue

            i += 1
            if i == quantitiesSize:
                retVal = True
                break
            remaining = quantities[i]

        return retVal

    def minimizedMaximum(self, n: int, quantities: List[int]) -> int:
        retVal = 0

        left = 0
        right = max(quantities)
        while left < right:
            middle = (left + right) // 2
            if self.canDistribute(middle, quantities, n) == True:
                right = middle
            else:
                left = middle + 1
        retVal = left

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, quantities in zip([6, 7, 1], [[11, 6], [15, 10, 10], [100000]]):
            # /* Example
            #  *  Input: n = 6, quantities = [11,6]
            #  *  Output: 3
            #  *
            #  *  Input: n = 7, quantities = [15,10,10]
            #  *  Output: 5
            #  *
            #  *  Input: n = 1, quantities = [100000]
            #  *  Output: 100000
            #  */
            logging.info("Input: n = %s, quantities = %s", n, quantities)

            retVal = pSolution.minimizedMaximum(n, quantities)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
