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
    def minCapability(self, nums: List[int], k: int) -> int:
        retVal = 0

        totalHouses = len(nums)
        left = 1
        right = max(nums)
        while left < right:
            middle = (left + right) // 2
            possibleThefts = 0

            index = 0
            while index < totalHouses:
                if nums[index] <= middle:
                    possibleThefts += 1
                    index += 2  # Skip the next house to maintain the non-adjacent condition
                else:
                    index += 1

            if possibleThefts >= k:
                right = middle
            else:
                left = middle + 1
        retVal = left

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k in zip([[2, 3, 5, 9],  [2, 7, 9, 3, 1]], [2, 2]):
            # /* Example
            #  *  Input: nums = [2,3,5,9], k = 2
            #  *  Output: 5
            #  *
            #  *  Input: nums = [2,7,9,3,1], k = 2
            #  *  Output: 2
            #  */
            logging.info("Input: nums = %s, k = %s", nums, k)

            retVal = pSolution.minCapability(nums, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
