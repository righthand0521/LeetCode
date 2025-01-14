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
    def findThePrefixCommonArray(self, A: List[int], B: List[int]) -> List[int]:
        retVal = None

        ASize = len(A)
        retVal = [0] * ASize

        frequency = [0] * (ASize+1)
        commonCount = 0
        for currentIndex in range(ASize):
            frequency[A[currentIndex]] += 1
            if frequency[A[currentIndex]] == 2:
                commonCount += 1

            frequency[B[currentIndex]] += 1
            if frequency[B[currentIndex]] == 2:
                commonCount += 1

            retVal[currentIndex] = commonCount

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for A, B in zip([[1, 3, 2, 4], [2, 3, 1]], [[3, 1, 2, 4], [3, 1, 2]]):
            # /* Example
            #  *  Input: A = [1,3,2,4], B = [3,1,2,4]
            #  *  Output: [0,2,3,4]
            #  *
            #  *  Input: A = [2,3,1], B = [3,1,2]
            #  *  Output: [0,1,3]
            #  */
            logging.info("Input: A = %s, B = %s", A, B)

            retVal = pSolution.findThePrefixCommonArray(A, B)
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
