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
    def check(self, r: int, k: int, val: int, cnt: List[int], stationsSize: int) -> bool:
        retVal = True

        diff = cnt.copy()
        total = 0
        remaining = k
        for i in range(stationsSize):
            total += diff[i]
            if total >= val:
                continue

            add = val - total
            if remaining < add:
                retVal = False
                break

            remaining -= add
            end = min(stationsSize, i + 2 * r + 1)
            diff[end] -= add
            total += add

        return retVal

    def maxPower(self, stations: List[int], r: int, k: int) -> int:
        retVal = 0

        stationsSize = len(stations)

        cnt = [0] * (stationsSize + 1)
        for i in range(stationsSize):
            left = max(0, i - r)
            right = min(stationsSize, i + r + 1)
            cnt[left] += stations[i]
            cnt[right] -= stations[i]

        low = min(stations)
        high = sum(stations) + k
        while low <= high:
            middle = (low + high) // 2
            if self.check(r, k, middle, cnt, stationsSize):
                retVal = middle
                low = middle + 1
            else:
                high = middle - 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for stations, r, k in [[[1, 2, 4, 5, 0], 1, 2], [[4, 4, 4, 4], 0, 3]]:
            # /* Example
            #  *  Input: stations = [1,2,4,5,0], r = 1, k = 2
            #  *  Output: 5
            #  *
            #  *  Input: stations = [4,4,4,4], r = 0, k = 3
            #  *  Output: 4
            #  */
            logging.info("Input: stations = %s, r = %s, k = %s", stations, r, k)

            retVal = pSolution.maxPower(stations, r, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
