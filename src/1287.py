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
    def findSpecialInteger(self, arr: List[int]) -> int:
        retVal = 0

        arrSize = len(arr)
        # there is exactly one integer in the array that occurs more than 25% of the time
        shift = arrSize >> 2
        for i in range(arrSize-shift):
            if arr[i] != arr[i+shift]:
                continue
            retVal = arr[i]
            break

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for arr in [[1, 2, 2, 6, 6, 6, 6, 7, 10], [1, 1], [1, 1, 2, 2, 3, 3, 3, 3]]:
            # /* Example
            #  *  Input: arr = [1,2,2,6,6,6,6,7,10]
            #  *  Output: 6
            #  *
            #  *  Input: arr = [1,1]
            #  *  Output: 1
            #  *
            #  *  Input: [1,1,2,2,3,3,3,3]
            #  *  Output: 3
            #  */
            logging.info("Input: arr = %s", arr)

            retVal = pSolution.findSpecialInteger(arr)
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
