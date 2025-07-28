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
    def constrainedSubsetSum(self, nums: List[int], k: int) -> int:
        retVal = 0

        numsSize = len(nums)

        monotonicDeque = deque()
        dp = [0] * numsSize

        for i in range(numsSize):
            if monotonicDeque and i - monotonicDeque[0] > k:
                monotonicDeque.popleft()

            dp[i] = (dp[monotonicDeque[0]] if monotonicDeque else 0) + nums[i]
            while monotonicDeque and dp[monotonicDeque[-1]] < dp[i]:
                monotonicDeque.pop()

            if dp[i] > 0:
                monotonicDeque.append(i)

        retVal = max(dp)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k in zip([[10, 2, -10, 5, 20], [-1, -2, -3], [10, -2, -10, -5, 20]], [2, 1, 2]):
            # /* Example
            #  *  Input: nums = [10,2,-10,5,20], k = 2
            #  *  Output: 37
            #  *
            #  *  Input: nums = [-1,-2,-3], k = 1
            #  *  Output: -1
            #  *
            #  *  Input: nums = [10,-2,-10,-5,20], k = 2
            #  *  Output: 23
            #  */
            logging.info("Input: nums = %s, k = %s", nums, k)

            retVal = pSolution.constrainedSubsetSum(nums, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
