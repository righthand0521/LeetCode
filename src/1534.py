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
    def countGoodTriplets(self, arr: List[int], a: int, b: int, c: int) -> int:
        retVal = 0

        arrSize = len(arr)
        for i in range(arrSize):
            for j in range(i + 1, arrSize):
                for k in range(j + 1, arrSize):
                    if (abs(arr[i] - arr[j]) <= a) and (abs(arr[j] - arr[k]) <= b) and (abs(arr[i] - arr[k]) <= c):
                        retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for arr, a, b, c in zip([[3, 0, 1, 1, 9, 7], [1, 1, 2, 2, 3]], [7, 0], [2, 0], [3, 1]):
            # /* Example
            #  *  Input: arr = [3,0,1,1,9,7], a = 7, b = 2, c = 3
            #  *  Output: 4
            #  *
            #  *  Input: arr = [1,1,2,2,3], a = 0, b = 0, c = 1
            #  *  Output: 0
            #  */
            logging.info("Input: arr = %s, a = %s, b = %s, c = %s", arr, a, b, c)

            retVal = pSolution.countGoodTriplets(arr, a, b, c)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
