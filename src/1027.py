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
    def __init__(self):
        self.method = 1

    def longestArithSeqLength(self, nums: List[int]) -> int:
        retVal = 0

        if self.method == 1:
            dp = defaultdict()
            numsSize = len(nums)
            for right in range(numsSize):
                for left in range(0, right):
                    dp[(right, nums[right] - nums[left])
                       ] = dp.get((left, nums[right] - nums[left]), 1) + 1
            retVal = max(dp.values())
        elif self.method == 2:
            minNum = min(nums)
            maxNum = max(nums)
            diff = maxNum - minNum
            for interval in range(-diff, diff+1):
                dp = defaultdict(int)
                for num in nums:
                    idx = num - interval
                    if idx in dp:
                        dp[num] = max(dp.get(num, 0), dp[idx] + 1)
                        retVal = max(retVal, dp[num])
                    dp[num] = max(dp.get(num, 0), 1)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[3, 6, 9, 12], [9, 4, 7, 2, 10], [20, 1, 15, 3, 10, 5, 8]]:
            # /* Example
            #  *  Input: nums = [3,6,9,12]
            #  *  Output: 4
            #  *
            #  *  Input: nums = [9,4,7,2,10]
            #  *  Output: 3
            #  *
            #  *  Input: nums = [20,1,15,3,10,5,8]
            #  *  Output: 4
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.longestArithSeqLength(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
