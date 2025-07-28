import logging
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from copy import deepcopy
from functools import cache, lru_cache
from heapq import heapify, heappop, heappush
from itertools import accumulate
from math import ceil
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
    def maxKelements(self, nums: List[int], k: int) -> int:
        retVal = 0

        # Define a max-heap by using a min-heap with negative values
        maxHeap = [-i for i in nums]
        heapify(maxHeap)

        while k > 0:
            k -= 1
            # Retrieve the max element (invert the sign because it's stored as negative)
            maxElement = -heappop(maxHeap)
            retVal += maxElement

            heappush(maxHeap, -ceil(maxElement / 3))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k in zip([[10, 10, 10, 10, 10], [1, 10, 3, 3, 3]], [5, 3]):
            # /* Example
            #  *  Input: nums = [10,10,10,10,10], k = 5
            #  *  Output: 50
            #  *
            #  *  Input: nums = [1,10,3,3,3], k = 3
            #  *  Output: 17
            #  */
            logging.info("Input: nums = %s, k = %s", nums, k)

            retVal = pSolution.maxKelements(nums, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
