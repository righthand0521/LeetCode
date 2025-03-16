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
    def repairCars(self, ranks: List[int], cars: int) -> int:
        retVal = 0

        # The minimum possible time is 1
        # The maximum possible time is when the slowest mechanic (highest rank) repairs all cars
        left = 1
        right = cars * cars * ranks[0]
        while left < right:
            middle = (left + right) // 2

            carsRepaired = sum(int((middle / rank) ** 0.5) for rank in ranks)

            # If the total cars repaired is less than required, increase the time.  Otherwise, try a smaller time.
            if carsRepaired < cars:
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
        for ranks, cars in zip([[4, 2, 3, 1], [5, 1, 8]], [10, 6]):
            # /* Example
            #  *  Input: ranks = [4,2,3,1], cars = 10
            #  *  Output: 16
            #  *
            #  *  Input: ranks = [5,1,8], cars = 6
            #  *  Output: 16
            #  */
            logging.info("Input: ranks = %s, cars = %d", ranks, cars)

            retVal = pSolution.repairCars(ranks, cars)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
