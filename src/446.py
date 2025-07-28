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
    def numberOfArithmeticSlices(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)

        dp = [defaultdict(int) for _ in range(numsSize)]
        for i in range(numsSize):
            for j in range(i):
                diff = nums[i] - nums[j]
                count = dp[j][diff]
                retVal += count
                dp[i][diff] += count + 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[2, 4, 6, 8, 10], [7, 7, 7, 7, 7]]:
            # /* Example
            #  *  Input: nums = [2,4,6,8,10]
            #  *  Output: 7
            #  *
            #  *  Input: nums = [7,7,7,7,7]
            #  *  Output: 16
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.numberOfArithmeticSlices(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
