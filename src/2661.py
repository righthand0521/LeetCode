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
    def firstCompleteIndex(self, arr: List[int], mat: List[List[int]]) -> int:
        retVal = 0

        arrSize = len(arr)
        numToIndex = {}
        for i in range(arrSize):
            numToIndex[arr[i]] = i

        matRowSize = len(mat)
        matColSize = len(mat[0])
        retVal = float("inf")
        for row in range(matRowSize):
            lastElementIndex = float("-inf")
            for col in range(matColSize):
                indexVal = numToIndex[mat[row][col]]
                lastElementIndex = max(lastElementIndex, indexVal)
            retVal = min(retVal, lastElementIndex)
        for col in range(matColSize):
            lastElementIndex = float("-inf")
            for row in range(matRowSize):
                indexVal = numToIndex[mat[row][col]]
                lastElementIndex = max(lastElementIndex, indexVal)
            retVal = min(retVal, lastElementIndex)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for arr, mat in zip([[1,3,4,2],[2,8,7,4,1,3,5,6,9]],[[[1,4],[2,3]],[[3,2,5],[1,4,6],[8,7,9]]]):
            # /* Example
            #  *  Input: arr = [1,3,4,2], mat = [[1,4],[2,3]]
            #  *  Output: 2
            #  *
            #  *  Input: arr = [2,8,7,4,1,3,5,6,9], mat = [[3,2,5],[1,4,6],[8,7,9]]
            #  *  Output: 3
            #  */
            logging.info("Input: mat = %s", mat)

            retVal = pSolution.firstCompleteIndex(arr,mat)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
