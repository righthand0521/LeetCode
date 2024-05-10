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
    def kthSmallestPrimeFraction(self, arr: List[int], k: int) -> List[int]:
        retVal = []

        arrSize = len(arr)

        left = 0
        right = 1.0
        while left < right:
            middle = (left + right) / 2

            maxFraction = 0.0
            totalSmallerFractions = 0
            numeratorIdx = 0
            denominatorIdx = 0
            j = 1
            for i in range(arrSize - 1):
                while (j < arrSize) and (arr[i] >= middle * arr[j]):
                    j += 1

                totalSmallerFractions += (arrSize - j)

                if j == arrSize:
                    break

                fraction = arr[i] / arr[j]
                if fraction > maxFraction:
                    numeratorIdx = i
                    denominatorIdx = j
                    maxFraction = fraction

            if totalSmallerFractions == k:
                retVal = [arr[numeratorIdx], arr[denominatorIdx]]
                break
            elif totalSmallerFractions > k:
                right = middle
            else:
                left = middle

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for arr, k in zip([[1, 2, 3, 5], [1, 7]], [3, 1]):
            # /* Example
            #  *  Input: arr = [1,2,3,5], k = 3
            #  *  Output: [2,5]
            #  *
            #  *  Input: arr = [1,7], k = 1
            #  *  Output: [1,7]
            #  */
            logging.info("Input: arr = %s, k = %s", arr, k)

            retVal = pSolution.kthSmallestPrimeFraction(arr, k)
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
