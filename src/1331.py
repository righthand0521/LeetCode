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
    def arrayRankTransform(self, arr: List[int]) -> List[int]:
        retVal = []

        arrSize = len(arr)
        if arrSize == 0:
            return retVal

        sortArr = sorted(arr)

        rank = 1
        hashTable = defaultdict(int)
        hashTable[sortArr[0]] = rank

        for i in range(1, arrSize):
            if sortArr[i] > sortArr[i - 1]:
                rank += 1
            hashTable[sortArr[i]] = rank

        for value in arr:
            retVal.append(hashTable[value])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for arr in [[40, 10, 20, 30], [100, 100, 100], [37, 12, 28, 9, 100, 56, 80, 5, 12]]:
            # /* Example
            #  *  Input: arr = [40,10,20,30]
            #  *  Output: [4,1,2,3]
            #  *
            #  *  Input: arr = [100,100,100]
            #  *  Output: [1,1,1]
            #  *
            #  *  Input: arr = [37,12,28,9,100,56,80,5,12]
            #  *  Output: [5,3,4,2,8,6,7,1,3]
            #  */
            logging.info("Input: arr = %s", arr)

            retVal = pSolution.arrayRankTransform(arr)
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
