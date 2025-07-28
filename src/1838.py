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
    def maxFrequency(self, nums: List[int], k: int) -> int:
        retVal = 0

        nums.sort()

        numsSize = len(nums)
        current = 0
        left = 0
        for right in range(numsSize):
            target = nums[right]
            current += target

            if (right - left + 1) * target - current > k:
                current -= nums[left]
                left += 1
        retVal = numsSize - left

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k in zip([[1, 2, 4], [1, 4, 8, 13], [3, 9, 6]], [5, 5, 2]):
            # /* Example
            #  *  Input: nums = [1,2,4], k = 5
            #  *  Output: 3
            #  *
            #  *  Input: nums = [1,4,8,13], k = 5
            #  *  Output: 2
            #  *
            #  *  Input: nums = [3,9,6], k = 2
            #  *  Output: 1
            #  */
            logging.info("Input: nums = %s, k = %s", nums, k)

            retVal = pSolution.maxFrequency(nums, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
