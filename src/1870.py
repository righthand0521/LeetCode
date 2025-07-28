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
    def minSpeedOnTime(self, dist: List[int], hour: float) -> int:
        retVal = -1

        distSize = len(dist)
        if (distSize - 1) >= hour:
            return retVal

        # Tests are generated such that the answer will not exceed 10 ^ 7
        # and hour will have at most two digits after the decimal point.
        left = 1
        right = 1e7
        while left < right:
            middle = left + (right - left) // 2

            # /* Example: dist = [1,3,2], hour = 2.7
            #  *  Speed   Time Required
            #  *    1     (1/1) + (3/1) + (2/1) = 6
            #  *    2     (1/2) + (3/2) + (2/2) = 1 + 2 + 1 = 4
            #  *    3     (1/3) + (3/3) + (2/3) = 1 + 1 + 0.67 = 2.67
            #  *
            #  *   10^7
            #  */
            totalHour = 0
            for i in range(distSize - 1):
                totalHour += ((dist[i] + middle - 1) // middle)
            totalHour += (dist[distSize - 1] / middle)

            if totalHour > hour:
                left = middle + 1
            else:
                right = middle

        retVal = int(left)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for dist, hour in zip([[1, 3, 2], [1, 3, 2], [1, 3, 2], [1, 1, 100000]], [6, 2.7, 1.9, 2.01]):
            # /* Example
            #  *  Input: dist = [1,3,2], hour = 6
            #  *  Output: 1
            #  *
            #  *  Input: dist = [1,3,2], hour = 2.7
            #  *  Output: 3
            #  *
            #  *  Input: dist = [1,3,2], hour = 1.9
            #  *  Output: -1
            #  *
            #  *  Input: dist = [1,1,100000], hour = 2.01
            #  *  Output: 10000000
            #  */
            logging.info("Input: dist = %s, hour = %s", dist, hour)

            retVal = pSolution.minSpeedOnTime(dist, hour)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
