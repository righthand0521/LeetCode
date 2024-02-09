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
    def largestDivisibleSubset(self, nums: List[int]) -> List[int]:
        retVal = []

        numsSize = len(nums)

        nums.sort()

        dp = []
        for i in range(numsSize):
            dp.append([nums[i]])

        for i in range(numsSize):
            for j in range(i):
                if (nums[i] % nums[j] == 0) and (len(dp[j]) >= len(dp[i])):
                    dp[i] = dp[j] + [nums[i]]

            if len(retVal) < len(dp[i]):
                retVal = dp[i]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[1, 2, 3], [1, 2, 4, 8], [4, 8, 10, 240]]:
            # /* Example
            #  *  Input: nums = [1,2,3]
            #  *  Output: [1,2]
            #  *
            #  *  Input: nums = [1,2,4,8]
            #  *  Output: [1,2,4,8]
            #  *
            #  *  Input: nums = [4, 8, 10, 240]
            #  *  Output: [4,8,240]
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.largestDivisibleSubset(nums)
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
