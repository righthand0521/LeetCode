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
    def maxSubarraySum(self, nums: List[int], k: int) -> int:
        retVal = 0

        numsSize = len(nums)

        prefixSum = 0
        maxSum = -sys.maxsize
        kSum = [sys.maxsize // 2] * k
        kSum[k - 1] = 0
        for i in range(numsSize):
            prefixSum += nums[i]
            maxSum = max(maxSum, prefixSum - kSum[i % k])
            kSum[i % k] = min(kSum[i % k], prefixSum)
        retVal = maxSum

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k in [[[1, 2], 1], [[-1, -2, -3, -4, -5], 4], [[-5, 1, 2, -3, 4], 2]]:
            # /* Example
            #  *  Input: nums = [1,2], k = 1
            #  *  Output: 3
            #  *
            #  *  Input: nums = [-1,-2,-3,-4,-5], k = 4
            #  *  Output: -10
            #  *
            #  *  Input: nums = [-5,1,2,-3,4], k = 2
            #  *  Output: 4
            #  */
            logging.info("Input: nums = %s, k = %s", nums, k)

            retVal = pSolution.maxSubarraySum(nums, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
