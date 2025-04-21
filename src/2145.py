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
    def numberOfArrays(self, differences: List[int], lower: int, upper: int) -> int:
        retVal = 0

        minValue = 0
        maxValue = 0
        currentSum = 0
        for difference in differences:
            currentSum += difference
            minValue = min(minValue, currentSum)
            maxValue = max(maxValue, currentSum)
            if (maxValue - minValue) > (upper - lower):
                return retVal
        retVal = (upper - lower) - (maxValue - minValue) + 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for differences, lower, upper in zip([[1, -3, 4], [3, -4, 5, 1, -2], [4, -7, 2]], [1, -4, 3], [6, 5, 6]):
            # /* Example
            #  *  Input: differences = [1,-3,4], lower = 1, upper = 6
            #  *  Output: 2
            #  *
            #  *  Input: differences = [3,-4,5,1,-2], lower = -4, upper = 5
            #  *  Output: 4
            #  *
            #  *  Input: differences = [4,-7,2], lower = 3, upper = 6
            #  *  Output: 0
            #  */
            logging.info("Input: differences = %s, lower = %s, upper = %s", differences, lower, upper)

            retVal = pSolution.numberOfArrays(differences, lower, upper)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
