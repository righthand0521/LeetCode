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
    def minDays(self, bloomDay: List[int], m: int, k: int) -> int:
        retVal = -1

        bloomDaySize = len(bloomDay)
        if m * k > bloomDaySize:
            return retVal

        left = 0
        right = max(bloomDay)
        while left <= right:
            middle = (left + right) // 2

            bouquets = 0
            count = 0
            for day in bloomDay:
                if day <= middle:
                    count += 1
                else:
                    count = 0

                if count == k:
                    bouquets += 1
                    count = 0

            if bouquets >= m:
                retVal = middle
                right = middle - 1
            else:
                left = middle + 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for bloomDay, m, k in zip([[1, 10, 3, 10, 2], [1, 10, 3, 10, 2], [7, 7, 7, 7, 12, 7, 7]], [3, 3, 2], [1, 2, 3]):
            # /* Example
            #  *  Input: bloomDay = [1,10,3,10,2], m = 3, k = 1
            #  *  Output: 3
            #  *
            #  *  Input: bloomDay = [1,10,3,10,2], m = 3, k = 2
            #  *  Output: -1
            #  *
            #  *  Input: bloomDay = [7,7,7,7,12,7,7], m = 2, k = 3
            #  *  Output: 12
            #  */
            logging.info("Input: bloomDay = %s, m = %s, k = %s",
                         bloomDay, m, k)

            retVal = pSolution.minDays(bloomDay, m, k)
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
