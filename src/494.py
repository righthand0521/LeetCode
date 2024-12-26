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
    def findTargetSumWays(self, nums: List[int], target: int) -> int:
        retVal = 0

        totalSum = sum(nums)

        dp = [0] * (2 * totalSum + 1)
        dp[nums[0] + totalSum] = 1  # Adding nums[0]
        dp[-nums[0] + totalSum] += 1  # Subtracting nums[0]

        numsSize = len(nums)
        for index in range(1, numsSize):
            nextDp = [0] * (2 * totalSum + 1)
            for value in range(-totalSum, totalSum + 1):
                if dp[value + totalSum] <= 0:
                    continue
                nextDp[value + nums[index] + totalSum] += dp[value + totalSum]
                nextDp[value - nums[index] + totalSum] += dp[value + totalSum]
            dp = nextDp

        # Return the result if the target is within the valid range
        if abs(target) <= totalSum:
            retVal = dp[target + totalSum]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, target in zip([[1, 1, 1, 1, 1], [1]], [3, 1]):
            # /* Example
            #  *  Input: nums = [1,1,1,1,1], target = 3
            #  *  Output: 5
            #  *
            #  *  Input: nums = [1], target = 1
            #  *  Output: 1
            #  */
            logging.info("Input: nums = %s, target = %s", nums, target)

            retVal = pSolution.findTargetSumWays(nums, target)
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
