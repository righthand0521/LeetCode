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
    def minimumTime(self, time: List[int], totalTrips: int) -> int:
        retVal = 0

        left = 0
        right = min(time) * totalTrips
        while left < right:
            middle = left + (right - left) // 2

            tmpTrips = 0
            for iterator in time:
                tmpTrips += (middle//iterator)

            if tmpTrips < totalTrips:
                left = middle + 1
            else:
                right = middle
        retVal = left

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for time, totalTrips in zip([[1, 2, 3], [2], [5, 10, 10], [1]], [5, 1, 9, 4]):
            # /* Example
            #  *  Input: time = [1,2,3], totalTrips = 5
            #  *  Output: 3
            #  *
            #  *  Input: time = [2], totalTrips = 1
            #  *  Output: 2
            #  *
            #  *  Input: time = [5,10,10], totalTrips = 9
            #  *  Output: 25
            #  *
            #  *  Input: time = [1], totalTrips = 4
            #  *  Output: 4
            #  */
            logging.info("Input: time = %s, totalTrips = %d", time, totalTrips)

            retVal = pSolution.minimumTime(time, totalTrips)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
