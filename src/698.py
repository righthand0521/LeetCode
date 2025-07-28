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
    def canPartitionKSubsets(self, nums: List[int], k: int) -> bool:
        retVal = False

        sumOfNums = sum(nums)
        if sumOfNums % k:
            return retVal
        average = sumOfNums // k

        numsSize = len(nums)
        dpSize = (1 << numsSize)
        dp = [-1] * dpSize
        dp[0] = 0
        for i in range(1, dpSize):
            for key, value in enumerate(nums):
                if i & (1 << key) == 0:
                    continue
                j = i & ~(1 << key)

                if (dp[j] >= 0) and (dp[j] + value <= average):
                    dp[i] = (dp[j] + value) % average
                    break
        retVal = (dp[-1] == 0)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k in zip([[4, 3, 2, 3, 5, 2, 1], [1, 2, 3, 4]], [4, 3]):
            # /* Example
            #  *  Input: nums = [4,3,2,3,5,2,1], k = 4
            #  *  Output: true
            #  *
            #  *  Input: nums = [1,2,3,4], k = 3
            #  *  Output: false
            #  */
            logging.info("Input: nums = %s, k = %s", nums, k)

            retVal = pSolution.canPartitionKSubsets(nums, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
