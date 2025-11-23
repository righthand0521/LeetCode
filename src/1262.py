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
    def maxSumDivThree(self, nums: List[int]) -> int:
        retVal = 0

        dp = [0, -float("inf"), -float("inf")]
        for num in nums:
            tmp = dp[:]
            for i in range(3):
                tmp[(i + num % 3) % 3] = max(tmp[(i + num % 3) % 3], dp[i] + num)
            dp = tmp
        retVal = dp[0]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[3, 6, 5, 1, 8], [4], [1, 2, 3, 4, 4]]:
            # /* Example
            #  *  Input: nums = [3,6,5,1,8]
            #  *  Output: 18
            #  *
            #  *  Input: nums = [4]
            #  *  Output: 0
            #  *
            #  *  Input: nums = [1,2,3,4,4]
            #  *  Output: 12
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.maxSumDivThree(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
