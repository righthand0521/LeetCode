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
    def minimumAbsDifference(self, arr: List[int]) -> List[List[int]]:
        retVal = []

        arrSize = len(arr)

        arr.sort()
        minDiff = sys.maxsize
        for i in range(1, arrSize):
            diff = arr[i] - arr[i - 1]
            if diff < minDiff:
                minDiff = diff
                retVal = [[arr[i - 1], arr[i]]]
            elif diff == minDiff:
                retVal.append([arr[i - 1], arr[i]])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for arr in [[4, 2, 1, 3], [1, 3, 6, 10, 15], [3, 8, -10, 23, 19, -4, -14, 27]]:
            # /* Example
            #  *  Input: arr = [4,2,1,3]
            #  *  Output: [[1,2],[2,3],[3,4]]
            #  *
            #  *  Input: arr = [1,3,6,10,15]
            #  *  Output: [[1,3]]
            #  *
            #  *  Input: arr = [3,8,-10,23,19,-4,-14,27]
            #  *  Output: [[-14,-10],[19,23],[23,27]]
            #  */
            logging.info("Input: arr = %s", arr)

            retVal = pSolution.minimumAbsDifference(arr)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
