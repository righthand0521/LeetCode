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
    def maxOperations(self, nums: List[int], k: int) -> int:
        retVal = 0

        nums.sort()
        numsSize = len(nums)
        left = 0
        right = numsSize - 1
        while left < right:
            sum = nums[left] + nums[right]
            if sum == k:
                left += 1
                right -= 1
                retVal += 1
            elif sum < k:
                left += 1
            elif sum > k:
                right -= 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k in zip([[1, 2, 3, 4], [3, 1, 3, 4, 3]], [5, 6]):
            # /* Example
            #  *  Input: nums = [1,2,3,4], k = 5
            #  *  Output: 2
            #  *
            #  *  Input: nums = [3,1,3,4,3], k = 6
            #  *  Output: 1
            #  */
            logging.info("Input: nums = %s, k = %s", nums, k)

            retVal = pSolution.maxOperations(nums, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
