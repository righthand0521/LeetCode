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
    def relativeSortArray(self, arr1: List[int], arr2: List[int]) -> List[int]:
        retVal = []

        upper = max(arr1)
        frequency = [0] * (upper + 1)
        for x in arr1:
            frequency[x] += 1

        for x in arr2:
            for _ in range(frequency[x]):
                retVal.append(x)
            frequency[x] = 0

        for x in range(upper + 1):
            if frequency[x] > 0:
                for _ in range(frequency[x]):
                    retVal.append(x)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for arr1, arr2 in zip([[2, 3, 1, 3, 2, 4, 6, 7, 9, 2, 19], [28, 6, 22, 8, 44, 17]],
                              [[2, 1, 4, 3, 9, 6], [22, 28, 8, 6]]):
            # /* Example
            #  *  Input: arr1 = [2,3,1,3,2,4,6,7,9,2,19], arr2 = [2,1,4,3,9,6]
            #  *  Output: [2,2,2,1,4,3,3,9,6,7,19]
            #  *
            #  *  Input: arr1 = [28,6,22,8,44,17], arr2 = [22,28,8,6]
            #  *  Output: [22,28,8,6,17,44]
            #  */
            logging.info("Input: arr1 = %s, arr2 = %s", arr1, arr2)

            retVal = pSolution.relativeSortArray(arr1, arr2)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
