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
    def validPartition(self, nums: List[int]) -> bool:
        retVal = False

        numsSize = len(nums)
        dp = [True] + [False] * numsSize
        # dp[i] represents if the prefix of length i can form a valid partition
        #   dp[index]: dp[index - 2] && (nums[i - 1] == nums[i])
        #   dp[index]: dp[index - 3] && (nums[i - 2] == nums[i -1 ] == nums[i])
        #   dp[index]: dp[index - 3] && (nums[i - 2] + 2 == nums[i - 1] + 1 == nums[i])
        for i in range(numsSize):
            index = i + 1
            if (i > 0) and (nums[i-1] == nums[i]):
                dp[index] |= dp[index - 2]
            if (i > 1) and (nums[i-2] == nums[i - 1] == nums[i]):
                dp[index] |= dp[index - 3]
            if (i > 1) and (nums[i-2]+2 == nums[i - 1] + 1 == nums[i]):
                dp[index] |= dp[index - 3]
        retVal = dp[numsSize]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[4, 4, 4, 5, 6], [1, 1, 1, 2]]:
            # /* Example
            #  *  Input: nums = [4,4,4,5,6]
            #  *  Output: true
            #  *
            #  *  Input: nums = [1,1,1,2]
            #  *  Output: false
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.validPartition(nums)
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
