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
    def missingRolls(self, rolls: List[int], mean: int, n: int) -> List[int]:
        retVal = []

        rollsSize = len(rolls)
        total = mean * (rollsSize + n)
        for roll in rolls:
            total -= roll
        if (total > (6 * n)) or (total < n):
            return retVal

        average = total // n
        index = total % n

        retVal = [average] * n
        for i in range(index):
            retVal[i] += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for rolls, mean, n in zip([[3, 2, 4, 3], [1, 5, 6], [1, 2, 3, 4]], [4, 3, 6], [2, 4, 4]):
            # /* Example
            #  *  Input: rolls = [3,2,4,3], mean = 4, n = 2
            #  *  Output: [6,6]
            #  *
            #  *  Input: rolls = [1,5,6], mean = 3, n = 4
            #  *  Output: [2,3,2,2]
            #  *
            #  *  Input: rolls = [1,2,3,4], mean = 6, n = 4
            #  *  Output: []
            #  */
            logging.info("Input: rolls = %s, mean = %s, n = %s", rolls, mean, n)

            retVal = pSolution.missingRolls(rolls, mean, n)
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
