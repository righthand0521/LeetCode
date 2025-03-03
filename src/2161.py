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
    def pivotArray(self, nums: List[int], pivot: int) -> List[int]:
        retVal = []

        numsSize = len(nums)
        retVal = [0] * numsSize

        less = 0
        equal = 0
        greater = 0
        for num in nums:
            if num < pivot:
                equal += 1
            elif num == pivot:
                greater += 1
        greater += equal

        for num in nums:
            if num < pivot:
                retVal[less] = num
                less += 1
            elif num > pivot:
                retVal[greater] = num
                greater += 1
            else:
                retVal[equal] = num
                equal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, pivot in zip([[9, 12, 5, 10, 14, 3, 10], [-3, 4, 3, 2]], [10, 2]):
            # /* Example
            #  *  Input: nums = [9,12,5,10,14,3,10], pivot = 10
            #  *  Output: [9,5,3,10,10,12,14]
            #  *
            #  *  Input: nums = [-3,4,3,2], pivot = 2
            #  *  Output: [-3,2,4,3]
            #  */
            logging.info("Input: nums = %s, pivot = %s", nums, pivot)

            retVal = pSolution.pivotArray(nums, pivot)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
