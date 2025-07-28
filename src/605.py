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
    def canPlaceFlowers(self, flowerbed: List[int], n: int) -> bool:
        retVal = False

        flowerbedSize = len(flowerbed)
        for i in range(flowerbedSize):
            if flowerbed[i] == 1:
                continue

            if i == 0:
                if flowerbedSize == 1 or flowerbed[i+1] == 0:
                    n -= 1
                    flowerbed[i] = 1
            elif i == flowerbedSize - 1:
                if flowerbed[i-1] == 0:
                    n -= 1
                    flowerbed[i] = 1
            else:
                if flowerbed[i-1] == 0 and flowerbed[i+1] == 0:
                    n -= 1
                    flowerbed[i] = 1
        if n <= 0:
            retVal = True

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for flowerbed, n in zip([[1, 0, 0, 0, 1], [1, 0, 0, 0, 1], [0], [0], [1], [1]], [1, 2, 0, 1, 0, 1]):
            # /* Example
            # *  Input: flowerbed = [1, 0, 0, 0, 1], n = 1
            # *  Output: true
            # *
            # *  Input: flowerbed = [1, 0, 0, 0, 1], n = 2
            # *  Output: false
            # *
            # *  Input: flowerbed = [0], n = 0
            # *  Output: true
            # *
            # *  Input: flowerbed = [0], n = 1
            # *  Output: true
            # *
            # *  Input: flowerbed = [1], n = 0
            # *  Output: true
            # *
            # *  Input: flowerbed = [1], n = 1
            # *  Output: false
            # */
            logging.info("Input: flowerbed = %s, n = %d", flowerbed, n)

            retVal = pSolution.canPlaceFlowers(flowerbed, n)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
