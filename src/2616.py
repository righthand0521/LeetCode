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
    def countValidPairs(self, nums: List[int], threshold) -> int:
        retVal = 0

        index = 0
        numsSize = len(nums)
        while index < numsSize - 1:
            # If a valid pair is found, skip both numbers.
            if nums[index + 1] - nums[index] <= threshold:
                retVal += 1
                index += 1
            index += 1

        return retVal

    def minimizeMax(self, nums: List[int], p: int) -> int:
        retVal = 0

        nums.sort()

        left = 0
        right = nums[-1] - nums[0]
        while left < right:
            middle = left + (right - left) // 2
            # If there are enough pairs, look for a smaller threshold. Otherwise, look for a larger threshold.
            if self.countValidPairs(nums, middle) >= p:
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
        for nums, p in zip([[10, 1, 2, 7, 1, 3], [4, 2, 1, 2]], [2, 1]):
            # /* Example
            #  *  Input: nums = [10,1,2,7,1,3], p = 2
            #  *  Output: 1
            #  *
            #  *  Input: nums = [4,2,1,2], p = 1
            #  *  Output: 0
            #  */
            logging.info("Input: nums = %s, p = %s", nums, p)

            retVal = pSolution.minimizeMax(nums, p)
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
