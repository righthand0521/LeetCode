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
    def maximumElementAfterDecrementingAndRearranging(self, arr: List[int]) -> int:
        retVal = 1

        arr.sort()

        arrSize = len(arr)
        for i in range(1, arrSize):
            if arr[i] - retVal >= 1:
                retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for arr in [[2, 2, 1, 2, 1], [100, 1, 1000], [1, 2, 3, 4, 5], [100, 1, 3, 3, 3, 3, 3], [73, 98, 9]]:
            # /* Example
            #  *  Input: arr = [2,2,1,2,1]
            #  *  Output: 2
            #  *
            #  *  Input: arr = [100,1,1000]
            #  *  Output: 3
            #  *
            #  *  Input: arr = [1,2,3,4,5]
            #  *  Output: 5
            #  *
            #  *  Input: arr = [100,1,3,3,3,3,3]
            #  *  Output: 4
            #  *
            #  *  Input: arr = [73,98,9]
            #  *  Output: 3
            #  */
            logging.info("Input: arr = %s", arr)

            retVal = pSolution.maximumElementAfterDecrementingAndRearranging(
                arr)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
