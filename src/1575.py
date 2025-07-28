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

    def countRoutes(self, locations: List[int], start: int, finish: int, fuel: int) -> int:
        retVal = 0

        locationsSize = len(locations)

        dp = [[0] * (fuel + 1) for _ in range(locationsSize)]
        for i in range(fuel + 1):
            dp[finish][i] = 1

        for i in range(fuel + 1):
            for src in range(locationsSize):
                for dst in range(locationsSize):
                    if dst == src:
                        continue
                    if abs(locations[src] - locations[dst]) <= i:
                        dp[src][i] = (
                            dp[src][i] + dp[dst][i - abs(locations[src] - locations[dst])]) % self.MODULO

        retVal = dp[start][fuel]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for locations, start, finish, fuel in zip([[2, 3, 6, 8, 4], [4, 3, 1], [5, 2, 1]],
                                                  [1, 1, 0],
                                                  [3, 0, 2],
                                                  [5, 6, 3]):
            # /* Example
            #  *  Input: locations = [2,3,6,8,4], start = 1, finish = 3, fuel = 5
            #  *  Output: 4
            #  *
            #  *  Input: locations = [4,3,1], start = 1, finish = 0, fuel = 6
            #  *  Output: 5
            #  *
            #  *  Input: locations = [5,2,1], start = 0, finish = 2, fuel = 3
            #  *  Output: 0
            #  */
            logging.info("Input: locations = %s, start = %s, finish = %s, fuel = %s", locations, start, finish, fuel)

            retVal = pSolution.countRoutes(locations, start, finish, fuel)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
