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
    def findLengthOfShortestSubarray(self, arr: List[int]) -> int:
        retVal = 0

        arrSize = len(arr)

        right = arrSize - 1
        while (right > 0) and (arr[right] >= arr[right - 1]):
            right -= 1
        retVal = right

        left = 0
        while (left < right) and ((left == 0) or (arr[left - 1] <= arr[left])):
            while (right < arrSize) and (arr[left] > arr[right]):
                right += 1
            retVal = min(retVal, right - left - 1)
            left += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for arr in [[1, 2, 3, 10, 4, 2, 3, 5], [5, 4, 3, 2, 1], [1, 2, 3]]:
            # /* Example
            #  *  Input: arr = [1,2,3,10,4,2,3,5]
            #  *  Output: 3
            #  *
            #  *  Input: arr = [5,4,3,2,1]
            #  *  Output: 4
            #  *
            #  *  Input: arr = [1,2,3]
            #  *  Output: 0
            #  */
            logging.info("Input: arr = %s", arr)

            retVal = pSolution.findLengthOfShortestSubarray(arr)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
