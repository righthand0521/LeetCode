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
    def maxRunTime(self, n: int, batteries: List[int]) -> int:
        retVal = 0

        left = 1
        right = sum(batteries) // n
        while left < right:
            middle = right - (right - left) // 2

            total = 0
            for power in batteries:
                total += min(power, middle)
            if total // n >= middle:
                left = middle
            else:
                right = middle - 1

        retVal = left

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, batteries in zip([2, 2], [[3, 3, 3], [1, 1, 1, 1]]):
            # /* Example
            #  *  Input: n = 2, batteries = [3,3,3]
            #  *  Output: 4
            #  *
            #  *  Input: n = 2, batteries = [1,1,1,1]
            #  *  Output: 2
            #  */
            logging.info("Input: n = %s, batteries = %s", n, batteries)

            retVal = pSolution.maxRunTime(n, batteries)
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
